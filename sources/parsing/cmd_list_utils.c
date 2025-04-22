/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cmd_list_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:37:50 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/22 15:07:28 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	//ft_memset(new_node, 0 , sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->type = 10;
	new_node->fd = -1;
	new_node->fd_in = -1;
	new_node->fd_out = -1;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_cmd	*lst_add_new_cmd(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0 , sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->fd = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	lst_addback_cmd(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd *start;

	start = *cmd_list;
	if(start == NULL)
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
