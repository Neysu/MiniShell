/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:13:06 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/10 17:20:28 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds)
	{
		if (cmds->fd_in != -1)
			close(cmds->fd_in);
		if (cmds->fd_out != -1)
			close(cmds->fd_out);
		if (cmds->stdout_backup != -1)
			close(cmds->stdout_backup);
		if (cmds->stdin_backup != -1)
			close(cmds->stdin_backup);
		if (close_backups)
			restore_io(cmds);
	}
	close_pipe_fds(cmds, NULL);
}

void	exit_shell(t_data *data, int exit_code)
{
	if (data)
	{
		if (data->cmd)
			close_fds(data->cmd, true);
		free_data(data, true);
	}
	exit(exit_code);
}

void	print_exit_shell(t_data *data, int exit_code)
{
	write(STDERR_FILENO, "exit\n", 5);
	exit_shell(data, exit_code);
}
