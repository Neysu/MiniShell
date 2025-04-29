/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fd_utils.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:47:49 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/29 12:48:55 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

void	close_pipe_fds(t_cmd *cmds, t_cmd *skip_cmd)
{
	while (cmds)
	{
		if (cmds != skip_cmd && cmds->pipefd)
		{
			close(cmds->pipefd[0]);
			close(cmds->pipefd[1]);
		}
		cmds = cmds->next;
	}
}

bool	create_pipes(t_data *data)
{
	int			*fd;
	t_cmd		*tmp;

	tmp = data->cmd;
	while (tmp)
	{
		if (tmp->pipe_output || (tmp->prev && tmp->prev->pipe_output))
		{
			fd = malloc(sizeof * fd * 2);
			if (!fd || pipe(fd) != 0)
			{
				free_data(data, false);
				return (false);
			}
			tmp->pipefd = fd;
		}
		tmp = tmp->next;
	}
	return (true);
}

void	close_fds(t_cmd *cmds, bool close_backups)
{
	if (cmds)
	{
		if (cmds->fd_in != -1)
			close(cmds->fd_in);
		if (cmds->fd_out != -1)
			close(cmds->fd_out);
		if (close_backups)
			restore_io(cmds);
	}
	close_pipe_fds(cmds, NULL);
}
