/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:42:05 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/28 18:39:45 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	args_count(t_token *token)
{
	int	i;

	i = 0;
	while (token && (token->type == WORD || token->type == ENV))
	{
		token = token->next;
		i++;
	}
	return (i);
}

int	create_args_default_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb_args = args_count(temp);
	last_cmd->cmd = malloc(sizeof(char *) * (nb_args + 1));
	if (!last_cmd->cmd)
		return (FAILURE);
	temp = *token_node;
	i = 1;
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

char	**copy_default_in_new_tab(
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
