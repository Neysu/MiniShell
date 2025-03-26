/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 22:51:50 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/25 22:55:56 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	envp_check_tool(t_token *token)
{
	int	i;

	i = 0;
	while (token->str[i])
	{
		if (token->str[i] == '$')
		{
			if (token->prev && token->prev->type == HEREDOC)
				break;
			token->type = ENV;
			return ;
		}
		i++;
	}
}

int	envp_check(t_token **token_list)
{
	t_token	*temp;

	temp = *token_list;
	/* if the pipe is at the beginning of the list */
	if (temp->type == PIPE)
	{
		ft_putendl_fd("syntax error near unexpected token", 2);
		return (FAILURE);
	}
	while (temp)
	{
		envp_check_tool(temp);
		temp = temp->next;
	}
	return (SUCCESS);
}