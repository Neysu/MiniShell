/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   file_io.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:18:13 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/06 12:38:43 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	restore_io(t_cmd *cmd)
{
	int	ret;

	ret = true;
	if (!cmd)
		return (ret);
	if (cmd->stdin_backup != -1)
	{
		if (dup2(cmd->stdin_backup, STDIN_FILENO) == -1)
			ret = false;
		close(cmd->stdin_backup);
		cmd->stdin_backup = -1;
	}
	if (cmd->stdout_backup != -1)
	{
		if (dup2(cmd->stdout_backup, STDOUT_FILENO) == -1)
			ret = false;
		close(cmd->stdout_backup);
		cmd->stdout_backup = -1;
	}
	return (ret);
}

bool	redirect_io(t_cmd *cmd)
{
	int	ret;

	ret = true;
	if (!cmd)
		return (ret);
	cmd->stdin_backup = dup(STDIN_FILENO);
	if (cmd->stdin_backup == -1)
		ret = errmsg_cmd("dup", "stdin backup", strerror(errno), false);
	cmd->stdout_backup = dup(STDOUT_FILENO);
	if (cmd->stdout_backup == -1)
		ret = errmsg_cmd("dup", "stdout backup", strerror(errno), false);
	if (cmd->fd_in != -1)
		if (dup2(cmd->fd_in, STDIN_FILENO) == -1)
			ret = errmsg_cmd("dup2", cmd->infile, strerror(errno), false);
	if (cmd->fd_out != -1)
		if (dup2(cmd->fd_out, STDOUT_FILENO) == -1)
			ret = errmsg_cmd("dup2", cmd->outfile, strerror(errno), false);
	return (ret);
}
