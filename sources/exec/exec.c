/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:29 by elliot            #+#    #+#             */
/*   Updated: 2025/04/27 17:21:08 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

// void	exec_single(t_data *data, t_cmd *cmd_data)
// {
// 	pid_t	pid;
// 	int		status;

// 	pid = fork();
// 	if (pid == 0)
// 	{
// 		if (is_builtin(cmd_data))
// 		 	exec_buitlins(data, cmd_data);
// 		else
// 			exec_cmd(cmd_data, data->envp);
// 	}
// 	waitpid(pid, &status, 0);
// }

// int		exec(t_data *data)
// {
// 	t_cmd *current = data->cmd;

// 	while (current)
// 	{
// 		if (current->type == REDIRECT_OUT || current->type == REDIRECT_IN
// 			|| current->type == APPEND)
// 			redirect(current, data);
// 		else if (current->type == COMMAND && current->cmd && current->cmd[0])
// 			exec_single(data, current);
// 		current = current->next;
// 	}
// 	return (1);
// }

char	**env_to_str(t_envp *envp)
{
	char	**env;
	t_envp	*current;
	int		i;

	i = 0;
	env = ft_calloc(sizeof(char *), ft_envsize(envp));
	current = envp;
	while (current->next)
	{
		env[i] = ft_strdup(current->var);
		i++;
		current = current->next;
	}
	return (env);
}

bool	cmd_is_dir(char *cmd)
{
	struct stat	cmd_stat;

	ft_memset(&cmd_stat, 0, sizeof(cmd_stat));
	stat(cmd, &cmd_stat);
	return (S_ISDIR(cmd_stat.st_mode));
}

int	check_command_not_found(t_data *data, t_cmd *cmd)
{
	if (ft_strchr(cmd->cmd[0], '/') == NULL
		&& get_env_var_index(data->env_list, "PATH") != -1)
		return (errmsg_cmd(cmd->cmd[0], NULL, "command not found",
				CMD_NOT_FOUND));
	if (access(cmd->cmd[0], F_OK) != 0)
		return (errmsg_cmd(cmd->cmd[0], NULL, strerror(errno), CMD_NOT_FOUND));
	else if (cmd_is_dir(cmd->cmd[0]))
		return (errmsg_cmd(cmd->cmd[0], NULL, "Is a directory",
				CMD_NOT_EXECUTABLE));
	else if (access(cmd->cmd[0], F_OK | X_OK) != 0)
		return (errmsg_cmd(cmd->cmd[0], NULL, strerror(errno),
				CMD_NOT_EXECUTABLE));
	return (EXIT_SUCCESS);
}

static int	execute_sys_bin(t_data *data, t_cmd *cmd)
{
	if (cmd->cmd[0] == NULL)
		return (CMD_NOT_FOUND);
	if (cmd_is_dir(cmd->cmd[0]))
		return (CMD_NOT_FOUND);
	cmd->path = get_cmd_path(data, cmd->cmd[0]);
	if (!cmd->path)
		return (CMD_NOT_FOUND);
	if (execve(cmd->path, cmd->cmd, data->env_list) == -1)
		errmsg_cmd("execve", NULL, strerror(errno), errno);
	return (EXIT_FAILURE);
}

static int	execute_local_bin(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = check_command_not_found(data, cmd);
	if (ret != 0)
		return (ret);
	if (execve(cmd->cmd[0], cmd->cmd, data->env_list) == -1)
		return (errmsg_cmd("execve", NULL, strerror(errno), errno));
	return (EXIT_FAILURE);
}
/*    PIPE START     */

bool	set_pipe_fds(t_cmd *cmds, t_cmd *c)
{
	if (!c)
		return (false);
	if (c->prev && c->prev->pipe_output)
		dup2(c->prev->pipefd[0], STDIN_FILENO);
	if (c->pipe_output)
		dup2(c->pipefd[1], STDOUT_FILENO);
	close_pipe_fds(cmds, c);
	return (true);
}

/*    PIPE END     */

int	exec_cmd(t_data *data, t_cmd *cmd)
{
	int	ret;

	if (!cmd || !cmd->cmd[0])
		exit_shell(data, errmsg_cmd("child", NULL,
				"parsing error: no command to execute!", EXIT_FAILURE));
	if (!check_infile_outfile(cmd))
		exit_shell(data, EXIT_FAILURE);
	set_pipe_fds(data->cmd, cmd);
	redirect_io(cmd);
	close_fds(data->cmd, false);
	if (ft_strchr(cmd->cmd[0], '/') == NULL)
	{
		ret = exec_buitlins(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
		ret = execute_sys_bin(data, cmd);
		if (ret != CMD_NOT_FOUND)
			exit_shell(data, ret);
	}
	ret = execute_local_bin(data, cmd);
	exit_shell(data, ret);
	return (ret);
}
