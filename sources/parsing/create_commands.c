/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:44:03 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/28 18:44:11 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd) * 1);
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0 , sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->args = NULL;
	new_node->pipefd = NULL;
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

void parse_word(void)
{

}

void create_commands(t_data *data, t_token *token)
{
	t_token *temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_addback_cmd(&data->cmd, lst_new_cmd());
		if (temp->type == WORD || temp->type == ENV)
			parse_word();
	}

}
