/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 00:06:46 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/24 01:08:38 by username         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		open_out(char *file, t_cmd *cmd_data)
{
	cmd_data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd_data->outfile == -1)
		return (1);
	dup2(cmd_data->outfile, STDOUT_FILENO);
	close(cmd_data->outfile);
	return (0);
}

int	redirect_out(t_cmd *cmd_data)
{
	close(cmd_data->pipefd[0]);
	if (dup2(cmd_data->pipefd[1], STDOUT_FILENO) == -1)
		return (1);
	(close(cmd_data->pipefd[1]));
	return (0);
}

int		open_inf(char *file, t_cmd *cmd_data)
{
	cmd_data->infile = open(file, O_RDONLY);
	if (cmd_data->infile == -1)
		return (ft_putendl_fd("NOP", 2), 1);
	dup2(cmd_data->infile, STDIN_FILENO);
	close(cmd_data->infile);
	return (0);
}

int	redirect_inf(t_cmd *cmd_data)
{
	(close(cmd_data->pipefd[1]));
	if (dup2(cmd_data->pipefd[0], STDIN_FILENO) == -1)
		return (1);
	(close(cmd_data->pipefd[0]));
	return (0);
}
