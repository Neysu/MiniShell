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

void	pipe_cmd(t_data	*data, t_cmd *cmd_data)
{
	pid_t	pid;
	pid_t	pid2;

	pipe(cmd_data->pipefd);
	pid = fork();
	
	if (pid == 0)
	{
		redirect_out(cmd_data);
		exec_cmd(cmd_data, data->envp);
	}

	pid2 = fork();

	if (pid2 == 0)
	{
		redirect_inf(cmd_data);
		exec_cmd(cmd_data->next, data->envp);
	}
}

int	exec(t_data *data)
{
	t_token		*current;

	current = data->token;
	while (current)
	{
		if (current->type == PIPE)
			pipe_cmd(data, data->cmd_data);
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
