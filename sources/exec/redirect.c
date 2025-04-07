/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:39:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/07 01:02:43 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

int		open_inf(char *file, t_cmd *cmd_data)
{
	int	infile;
	(void)cmd_data;

	infile = open(file, O_RDONLY);
	if (infile == -1)
		return (ft_putendl_fd("Error infile", 2), 1);
	dup2(infile, STDIN_FILENO);
	close(infile);
	return (0);
}

int		open_out(char *file, t_cmd *cmd_data)
{
	int	outfile;

	if (cmd_data->type == REDIRECT_OUT)
		outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd_data->type == APPEND)
		outfile = open(file, O_WRONLY | O_CREAT | O_APPEND, 0644);
	if (outfile == -1)
		return (1);
	dup2(outfile, STDOUT);
	close(outfile);
	return (0);
}

int	redirect_inf(t_cmd *cmd_data, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*file;

	file = ft_strdup(cmd_data->next->cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		if (open_inf(file, cmd_data))
			(free(file), exit(1));
		exec_cmd(cmd_data, data->envp);
	}
	free(file);
	waitpid(pid, &status, 0);
	return (0);
}

int	redirect_out(t_cmd *cmd_data, t_data *data)
{
	pid_t	pid;
	int		status;
	char	*file;

	file = ft_strdup(cmd_data->next->cmd[0]);
	pid = fork();
	if (pid == 0)
	{
		if (open_out(file, cmd_data))
			(free(file), exit(1));
		exec_cmd(cmd_data, data->envp);
	}
	free(file);
	waitpid(pid, &status, 0);
	return (0);
}

