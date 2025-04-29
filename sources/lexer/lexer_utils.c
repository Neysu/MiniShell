/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:20:56 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/29 12:27:10 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_separator(char *str, int i)
{
	if (((str[i] > 8 && str[i] < 14) || str[i] == 32))
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>')
		return (REDIRECT_OUT);
	else if (str[i] == '<')
		return (REDIRECT_IN);
	else if (str[i] == '\0')
		return (END);
	else
		return (0);
}

int	check_quotes(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = SQUOTE;
	else if (str[i] == '\"' && status == DEFAULT)
		status = DQUOTE;
	else if (str[i] == '\'' && status == SQUOTE)
		status = DEFAULT;
	else if (str[i] == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

t_token	*lst_new_token(char *str, char *str_backup, int type, int status)
{
	t_token	*new_node;

	new_node = malloc(sizeof(t_token) * 1);
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->str_backup = str_backup;
	new_node->var_exist = false;
	new_node->type = type;
	new_node->status = status;
	new_node->join = false;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	lst_addback_token(t_token **token_list, t_token *new_node)
{
	t_token	*start;

	start = *token_list;
	if (start == NULL)
	{
		*token_list = new_node;
		return ;
	}
	if (token_list && *token_list && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}
