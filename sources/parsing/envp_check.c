/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   envp_check.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/23 17:51:19 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/23 17:52:31 by rureshet         ###   ########.fr       */
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
		error_message("syntax error near unexpected token");
		return (FAILURE);
	}
	while (temp)
	{
		envp_check_tool(temp);
		temp = temp->next;
	}
	return (SUCCESS);
}
