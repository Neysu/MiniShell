/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   execute.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:47:10 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/29 12:48:35 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
