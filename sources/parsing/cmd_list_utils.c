/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:37:50 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/03 17:04:52 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	init_cmd(t_cmd **cmd)
{
	(*cmd)->cmd = NULL;
	(*cmd)->path = NULL;
	(*cmd)->pipe_output = false;
	(*cmd)->pipefd = 0;
	(*cmd)->fd = -1;
	(*cmd)->fd_in = -1;
	(*cmd)->fd_out = -1;
	(*cmd)->infile = NULL;
	(*cmd)->outfile = NULL;
	(*cmd)->stdin_backup = -1;
	(*cmd)->stdout_backup = -1;
	(*cmd)->heredoc_delimiter = NULL;
	(*cmd)->heredoc_quotes = false;
	(*cmd)->prev = NULL;
	(*cmd)->next = NULL;
}

t_cmd	*lst_new_cmd(bool value)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	new_node->pipe_output = value;
	init_cmd(&new_node);
	return (new_node);
}

t_cmd	*lst_add_new_cmd(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0, sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->fd = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	lst_addback_cmd(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd	*start;

	start = *cmd_list;
	if (start == NULL)
	{
		*cmd_list = new_node;
		return ;
	}
	if (cmd_list && *cmd_list && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

t_cmd	*lst_last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}
