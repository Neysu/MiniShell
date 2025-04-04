/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:44:03 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/04 21:36:23 by rureshet         ###   ########.fr       */
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
	new_node->type = 0;
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
	new_node->cmd_name = NULL;
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

int	args_count(t_token *token)
{
	int	i;

	i = 0;
	while(token && (token->type == WORD || token->type == ENV))
	{
		token = token->next;
		i++;
	}
	return(i);
}

int	create_args_default_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb_args = args_count(temp);
	last_cmd->cmd = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->cmd)
		return (FAILURE);
	temp = *token_node;
	i = 0;
	last_cmd->cmd[i] = ft_strdup(last_cmd->cmd_name);
	i++;
	while (temp->type == WORD || temp->type == ENV)
	{
		last_cmd->cmd[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->cmd[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

static char	**copy_default_in_new_tab(
	int len, char **new_tab, t_cmd *last_cmd, t_token **tk_node)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tk_node;
	while (i < len)
	{
		new_tab[i] = last_cmd->cmd[i];
		i++;
	}
	while (temp->type == WORD || temp->type == ENV)
	{
		new_tab[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	add_args_default_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	while (temp->type == WORD || temp->type == ENV)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (last_cmd->cmd[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_default_in_new_tab(len, new_tab, last_cmd, token_node);
	free(last_cmd->cmd);
	last_cmd->cmd = new_tab;
	*token_node = temp;
	return (SUCCESS);
}

int	fill_args(t_token **token_node, t_cmd *last_cmd)
{
	if (last_cmd && !(last_cmd->cmd))
		return (create_args_default_mode(token_node, last_cmd));
	else
		return (add_args_default_mode(token_node, last_cmd));
	return (SUCCESS);
}

void parse_word(t_cmd **cmd, t_token **token)
{
	t_token		*temp;
	t_cmd	*last_cmd;

	temp = *token;
	while (temp->type == WORD || temp->type == ENV)
	{
		last_cmd = lst_last_cmd(*cmd);
		fill_args(&temp, last_cmd);
	}
	*token = temp;
}

void create_commands(t_data *data, t_token *token)
{
	t_token *temp;

	temp = token;
	if ( temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_addback_cmd(&data->cmd, lst_new_cmd());
		if (temp->type == WORD || temp->type == ENV)
			parse_word(&data->cmd, &temp);
	}
}
