/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:29 by elliot            #+#    #+#             */
/*   Updated: 2025/03/26 00:35:46 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	pipe_cmd(t_data *data, t_cmd *cmd_data)
{
	pid_t pid;
	int pipefd[2], status;

	if (!cmd_data || !cmd_data->next)
		return (perror("Invalid input or no pipes"), exit(EXIT_FAILURE));
	while (cmd_data)
	{
		if (pipe(pipefd) == -1)
			return (perror("pipe failed"), exit(EXIT_FAILURE));
		if ((pid = fork()) == -1)
			return (perror("fork failed"), exit(EXIT_FAILURE));
		if (pid == 0)
		{
			if (cmd_data->prev)
				dup2(pipefd[0], STDIN_FILENO);
			if (cmd_data->next)
				dup2(pipefd[1], STDOUT_FILENO);
			close(pipefd[0]), close(pipefd[1]);
			exec_cmd(cmd_data, data->envp);
			perror("exec_cmd failed"), exit(EXIT_FAILURE);
		}
		close(pipefd[0]), close(pipefd[1]);
		cmd_data = cmd_data->next;
	}
	while (waitpid(pid, &status, 0) > 0);
}


int	exec(t_data *data)
{
	t_token		*current;

	current = data->token;
	while (current)
	{
		if (current->type == PIPE)
			pipe_cmd(data, data->cmd_data);
		else if (current->type == REDIRECT_OUT)
			
		current = current->next;
	}
	return (0);
}

int	exec_cmd(t_cmd *cmd_data, t_envp *envp_data)
{
	char	*path;
	char	**envp;

	path = findcmd(cmd_data, envp_data);
	if (!path)
		perror(cmd_data->cmd[0]);
	envp = env_to_str(envp_data);
	if (execve(path, cmd_data->cmd, envp) == -1)
		(ft_printf(ERRORCMD, cmd_data->cmd[0]), ft_free_arr(cmd_data->cmd), ft_free_arr(envp), exit(1));
	return (0);
}
