/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:18:13 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/11 01:12:41 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	open_file(t_cmd *cmd_data)
{
	if (cmd_data->type == REDIRECT_OUT)
	{
		cmd_data->fd = open(cmd_data->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0644);
		if (cmd_data->fd == -1)
			return (perror("outfile"), 1);
	}
	else if (cmd_data->type == APPEND)
	{
		cmd_data->fd = open(cmd_data->outfile, O_WRONLY | O_CREAT | O_APPEND, 0644);
		if (cmd_data->fd == -1)
			return (perror("outfile"), 1);
	}
	else if (cmd_data->type == REDIRECT_IN)
	{
		cmd_data->fd = open(cmd_data->infile, O_RDONLY);
		if (cmd_data->fd == -1)
			return (perror("infile"), 1);
	}
	return (0);
}

void	ft_closefds(t_cmd *cmd_data)
{
	t_cmd	*current;

	current = cmd_data;
	while (current)
	{
		if (current->fd >= 0)
			close(current->fd);
		current = current->next;
	}
}

int	get_redirect(t_cmd *cmd_data)
{
	t_cmd	*current;

	current = cmd_data;
	while (current)
	{
		if (current->fd >= 0)
		{
			if (current->type == REDIRECT_IN)
			{
				if (dup2(current->fd, STDIN) == -1)
					return (perror("dup2"), 1);
			}
			if (current->type == REDIRECT_OUT || current->type == APPEND)
			{
				if (dup2(current->fd, STDOUT_FILENO) == -1)
					return (perror("dup2"), 1);
			}
			close(current->fd);
		}
		current = current->next;
	}
	return (0);
}

int	open_files(t_cmd *cmd_data, t_data *data)
{
	t_cmd	*current;

	(void)data;
	current = cmd_data;
	while (current)
	{
		if (current->next && (current->type == REDIRECT_OUT || current->type == APPEND
			|| current->type == REDIRECT_IN))
		{
			if (open_file(current))
				return (ft_putendl_fd("error file opening", STDERR), 1);
		}
		current = current->next;
	}
	return (0);
}
