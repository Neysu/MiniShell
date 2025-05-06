/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fill_args.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 15:12:02 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/06 13:43:08 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	create_args_echo_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		nb_args;
	t_token	*temp;
	int		i;

	remove_empty_var_args(token_node);
	temp = *token_node;
	nb_args = count_args(temp);
	last_cmd->cmd = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->cmd)
		return (FAILURE);
	i = 0;
	last_cmd->cmd[i] = ft_strdup(last_cmd->command);
	i++;
	while (temp->type == WORD || temp->type == ENV)
	{
		if (temp->join == true)
			last_cmd->cmd[i] = join_vars(&temp);
		else
			last_cmd->cmd[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->cmd[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

static int	add_args_echo_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		len;
	int		nb_args;
	char	**new_tab;
	t_token	*temp;

	remove_empty_var_args(token_node);
	temp = *token_node;
	nb_args = count_args(temp);
	len = 0;
	while (last_cmd->cmd[len])
		len++;
	new_tab = malloc(sizeof(char *) * (nb_args + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_in_new_tab(len, new_tab, last_cmd, temp);
	free(last_cmd->cmd);
	last_cmd->cmd = new_tab;
	while (temp->type == WORD || temp->type == ENV)
		temp = temp->next;
	*token_node = temp;
	return (SUCCESS);
}

static int	create_args_default_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb_args = count_args(temp);
	last_cmd->cmd = malloc(sizeof(char *) * (nb_args + 2));
	if (!last_cmd->cmd)
		return (FAILURE);
	temp = *token_node;
	i = 0;
	last_cmd->cmd[i] = ft_strdup(last_cmd->command);
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
	if (!ft_strcmp(last_cmd->command, "echo"))
	{
		if (!(last_cmd->cmd))
			return (create_args_echo_mode(token_node, last_cmd));
		else
			return (add_args_echo_mode(token_node, last_cmd));
	}
	else
	{
		if (last_cmd && !(last_cmd->cmd))
			return (create_args_default_mode(token_node, last_cmd));
		else
			return (add_args_default_mode(token_node, last_cmd));
	}
	return (SUCCESS);
}
