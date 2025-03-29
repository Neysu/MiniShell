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

static char	*find_file(t_token *token)
{
	t_token	*current;
	char	*file;

	current = token;
	file = NULL;
	while (current->next)
	{
		if (current->type == REDIRECT_OUT && current->next->type == WORD)
			file = ft_strdup(current->next->str);
		current = current->next;
	}
	return (file);
}

int	redirect_out(t_cmd *cmd_data, t_data *data)
{
	pid_t	pid;
	int		status;
	printf("aaaaaaaaaaaaaaaaaaaaaaaaaa\n");

	pipe(cmd_data->pipefd);
	pid = fork();
	cmd_data->file = find_file(data->token);
	printf("%s\n", cmd_data->file);
	if (pid == 0)
	{
		if (open_out(cmd_data->file, cmd_data))
			return (1);
		exec_cmd(cmd_data, data->envp);
	}
	free(cmd_data->file);
	waitpid(pid, &status, 0);
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
