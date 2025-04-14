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
		current = cmd_data;
		if (get_redirect(cmd_data))
			exit(1);
		exec_cmd(current, data->envp);
		exit(1);
	}
	ft_closefds(cmd_data);
	waitpid(pid, &status, 0);
	return (0);
}

