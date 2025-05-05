/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   args_handling.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:42:05 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/05 11:46:18 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_arguments(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == ENV))
	{
		i++;
		temp = temp->next;
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
	nb_args = count_arguments(temp);
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

void	remove_empty_var_args(t_token **tokens)
{
	t_token	*temp;

	temp = *tokens;
	while (temp->type == WORD || temp->type == ENV)
	{
		if (temp->type == ENV && temp->str[0] == '\0'
			&& temp->var_exists == false)
		{
			temp = temp->next;
			if (temp == (*tokens)->next)
				(*tokens) = (*tokens)->next;
			lstdelone_token(temp->prev, free_ptr);
		}
		else
			temp = temp->next;
	}
}

char	*join_vars(t_token **token_node)
{
	t_token	*temp;
	char	*str;

	temp = *token_node;
	str = ft_strdup(temp->str);
	while (temp->type == ENV && temp->next->type == ENV
		&& temp->next->join == true)
	{
		str = ft_strjoin(str, temp->next->str);
		temp = temp->next;
	}
	*token_node = temp;
	return (str);
}

int	count_args(t_token *temp)
{
	int	i;

	i = 0;
	while (temp && (temp->type == WORD || temp->type == ENV))
	{
		if (temp->type == ENV && temp->join == true)
		{
			while (temp->type == ENV && temp->join == true)
				temp = temp->next;
			i++;
		}
		else
		{
			i++;
			temp = temp->next;
		}
	}
	return (i);
}

char	**copy_in_new_tab(int len, char **new_tab,
			t_cmd *last_cmd, t_token *tmp)
{
	int	i;

	i = 0;
	while (i < len)
	{
		new_tab[i] = last_cmd->cmd[i];
		i++;
	}
	while (tmp->type == WORD || tmp->type == ENV)
	{
		if (tmp->join == true)
			new_tab[i] = join_vars(&tmp);
		else
			new_tab[i] = ft_strdup(tmp->str);
		i++;
		tmp = tmp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	create_args_echo_mode(t_token **token_node, t_cmd *last_cmd)
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

int	add_args_echo_mode(t_token **token_node, t_cmd *last_cmd)
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
