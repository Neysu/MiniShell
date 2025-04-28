/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/04/28 20:17:12 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(t_cmd *cmd_data)
{
	if (!cmd_data || !cmd_data->cmd || !cmd_data->cmd[0])
		return (0);
	if (!ft_strncmp(cmd_data->cmd[0], "echo", -1))
		return (ft_putendl_fd("echo is on", STDERR), 1);
	if (!ft_strncmp(cmd_data->cmd[0], "cd", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "pwd", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "export", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "unset", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "env", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "exit", -1))
		return (1);
	return (0);
}

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipefd)
		{
			close(cmds->pipefd[0]);
			close(cmds->pipefd[1]);
		}
		cmds = cmds->next;
	}
}

bool	create_pipes(t_data *data)
{
	int			*fd;
	t_cmd		*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			tmp->pipefd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds)
	{
		if (cmds->fd_in != -1)
			close(cmds->fd_in);
		if (cmds->fd_out != -1)
			close(cmds->fd_out);
		if (close_backups)
			restore_io(cmds);
	}
	close_pipe_fds(cmds, NULL);
}

int	get_children(t_data *data)
{
	pid_t	wpid;
	int		status;
	int		save_status;

	close_fds(data->cmd, false);
	save_status = 0;
	wpid = 0;
	while (wpid != -1 || errno != ECHILD)
	{
		wpid = waitpid(-1, &status, 0);
		if (wpid == data->pid)
			save_status = status;
		continue ;
	}
	if (WIFSIGNALED(save_status))
		status = 128 + WTERMSIG(save_status);
	else if (WIFEXITED(save_status))
		status = WEXITSTATUS(save_status);
	else
		status = save_status;
	return (status);
}

int	create_children(t_data *data)
{
	t_cmd	*cmd;

	cmd = data->cmd;
	while (data->pid != 0 && cmd)
	{
		data->pid = fork();
		if (data->pid == -1)
			return (errmsg_cmd("fork", NULL, strerror(errno), EXIT_FAILURE));
		else if (data->pid == 0)
			exec_cmd(data, cmd);
		cmd = cmd->next;
	}
	return (get_children(data));
}

bool	check_infile_outfile(t_cmd *cmd)
{
	if (!cmd || (!cmd->infile && !cmd->outfile))
		return (true);
	if ((cmd->infile && cmd->fd_in == -1)
		|| (cmd->outfile && cmd->fd_out == -1))
		return (false);
	return (true);
}

int	prep_for_exec(t_data *data)
{
	if (!data || !data->cmd)
		return (EXIT_SUCCESS);
	if (!data->cmd->cmd[0])
	{
		if ((data->cmd->infile || data->cmd->outfile
				|| data->cmd->heredoc_delimiter)
			&& !check_infile_outfile(data->cmd))
			return (EXIT_FAILURE);
		return (EXIT_SUCCESS);
	}
	if (!create_pipes(data))
		return (EXIT_FAILURE);
	return (CMD_NOT_FOUND);
}

int	execute(t_data *data)
{
	int	ret;

	ret = prep_for_exec(data);
	if (ret != CMD_NOT_FOUND)
		return (ret);
	if (!data->cmd->pipe_output && !data->cmd->prev
		&& check_infile_outfile(data->cmd))
	{
		redirect_io(data->cmd);
		ret = exec_buitlins(data, data->cmd);
		restore_io(data->cmd);
	}
	if (ret != CMD_NOT_FOUND)
		return (ret);
	return (create_children(data));
}

/*    exec END     */

void	parsing(t_data *data)
{
	char	**user_input;
	int		i;

	if (data->user_input == NULL)
		print_exit_shell(data, data->exit_code);
	user_input = ft_split(data->user_input, ';');
	if (!user_input)
		exit_shell(data, EXIT_FAILURE);
	i = 0;
	while (user_input[i])
	{
		data->user_input = ft_strdup(user_input[i]);
		if (parser_user_input(data) == true)
		{
			data->exit_code = execute(data);
		}
		else
			data->exit_code = 1;
		i++;
		free_data(data, false);
	}
	free_str_tab(user_input);
}

bool	parser_user_input(t_data *data)
{
	if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	else if (input_is_space(data->user_input))
		return (true);
	add_history(data->user_input);
	if (token_generator(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	if (envp_check(&data->token) == FAILURE)
		return (false);
	expand_variables(data, &data->token);
	quotes_handler(data);
	create_commands(data, data->token);
	return (true);
}
