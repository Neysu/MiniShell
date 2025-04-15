/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:51:19 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/15 18:17:16 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	envp_check_tool(t_token **token)
{
	int	i;

	i = 0;
	while ((*token)->str[i])
	{
		if ((*token)->str[i] == '$')
		{
			if ((*token)->prev && (*token)->prev->type == HEREDOC)
				break;
			(*token)->type = ENV;
			return ;
		}
		i++;
	}
}

bool	is_consecutive(t_token *token)
{
	if (token->prev)
	{
		if (token->type == PIPE && token->prev->type == PIPE)
			return (true);
		if (token->type > PIPE && token->prev->type > PIPE)
			return (true);
		if (token->type == END && token->prev->type >= PIPE)
			return (true);
	}
	return(false);
}

int	check_syntax_operators(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	while (temp)
	{
		if(is_consecutive(temp) == true)
		{
			if (temp->type == END && temp->prev && temp->prev->type > PIPE)
				error_message("syntax error near unexpected token", "newline", true);
			else if (temp->type == END && temp->prev)
				error_message("syntax error near unexpected token", temp->prev->str, true);
			else
				error_message("syntax error near unexpected token", temp->str, true);
			return (FAILURE);
		}
		temp = temp->next;
	}
	return (SUCCESS);
}

int	envp_check(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	if (temp->type == PIPE)
	{
		error_message("syntax error near unexpected token", "|", true);
		return (FAILURE);
	}
	while (temp)
	{
		envp_check_tool(&temp);
		if (check_syntax_operators(&temp) == FAILURE)
			return (FAILURE);
		temp = temp->next;
	}
	return (SUCCESS);
}
