/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:39:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/14 21:07:01 by rureshet         ###   ########.fr       */
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
		current = current->next;
	}
	return (cmd_data);
}

t_cmd	*last_redirect(t_cmd *cmd_data)
{
	bool	cmd_end;

	cmd_end = true;
	while (cmd_data && is_redirect(cmd_data))
	{
		if (cmd_data->cmd && cmd_data->cmd[0])
			cmd_end = false;
		cmd_data = cmd_data->next;
	}
	if (cmd_end)
		cmd_data = cmd_data->next;
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
		exit(127);
	}
	cmd_data = last_redirect(cmd_data);
	ft_closefds(cmd_data);
	waitpid(pid, &status, 0);
	return (0);
}

