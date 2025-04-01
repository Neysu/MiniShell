/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   redirect.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/01 22:39:51 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/01 23:42:51 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	open_out(t_cmd	*cmd_data, t_data *data)
{
	pid_t	pid;
	int		fd;

	pipe(cmd_data->pipefd);

	pid = fork();
	if (pid == 0)
	{
		fd = open(cmd_data->next);
	}
}

