/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:39:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/10 23:42:44 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static t_cmd	*find_cmd(t_cmd *cmd_data)
{
	t_cmd	*current;

	current = cmd_data;
	while (current)
	{
		if (current->cmd && current->cmd[0])
			return (current);
	}
	return (cmd_data);
}

int	redirect(t_cmd *cmd_data, t_data *data)
{
	pid_t	pid;
	int		status;
	t_cmd	*current;

	if (open_files(cmd_data, data))
		return (1);
	pid = fork();
	if (pid == 0)
	{
		if (get_redirect(cmd_data))
			exit(1);
		current = find_cmd(cmd_data);
		if (is_builtin(current))
		 	exec_buitlins(data->user_input, data);
		else
			exec_cmd(current, data->envp);
		exit(1);
	}
	ft_closefds(cmd_data);
	waitpid(pid, &status, 0);
	return (0);
}

