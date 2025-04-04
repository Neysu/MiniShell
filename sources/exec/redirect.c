/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:39:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/03 19:34:40 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	redirect_inf(t_cmd *cmd_data)
{
	(close(cmd_data->pipefd[1]));
	if (dup2(cmd_data->pipefd[0], STDIN) == -1)
		return (1);
	(close(cmd_data->pipefd[0]));
	return (0);
}

int	redirect_out(t_cmd *cmd_data, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*file;

	pipe(cmd_data->pipefd);
	pid = fork();
	file = ft_strdup(data->cmd->cmd[0];
	if (pid == 0)
	{
		if (open_out(file, cmd_data) == 1)
			return (1);
		exec_cmd(cmd_data, data->envp);
	}
	free(file);
	waitpid(pid, &status, 0);
	return (0);
}

int		open_inf(char *file, t_cmd *cmd_data)
{
	cmd_data->infile = open(file, O_RDONLY);
	if (cmd_data->infile == -1)
		return (ft_putendl_fd("NOP", 2), 1);
	dup2(cmd_data->infile, STDIN);
	close(cmd_data->infile);
	return (0);
}

int		open_out(char *file, t_cmd *cmd_data)
{
	cmd_data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd_data->outfile == -1)
		return (1);
	dup2(cmd_data->outfile, STDOUT);
	close(cmd_data->outfile);
	return (0);
}

