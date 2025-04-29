/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler_utils.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:52:50 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/29 12:53:18 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\'' || str[i] == '\"') && status == DEFAULT)
		{
			if (str[i] == '\'')
				status = SQUOTE;
			if (str[i] == '\"')
				status = DQUOTE;
			i++;
			continue ;
		}
		else if ((str[i] == '\'' && status == SQUOTE)
			|| (str[i] == '\"' && status == DQUOTE))
		{
			status = DEFAULT;
			i++;
			continue ;
		}
		count++;
		i++;
	}
	return (count + 1);
}

bool	quote_and_status_default(t_token **token, int i)
{
	if (((*token)->str[i] == '\'' || (*token)->str[i] == '\"')
		&& (*token)->status == DEFAULT)
		return (true);
	else
		return (false);
}

void	change_status_quote(t_token **token, int *i)
{
	if ((*token)->str[*i] == '\'')
		(*token)->status = SQUOTE;
	if ((*token)->str[*i] == '\"')
		(*token)->status = DQUOTE;
	(*i)++;
}

bool	back_status_to_default(t_token **token, int *i)
{
	if (((*token)->str[*i] == '\'' && (*token)->status == SQUOTE)
		|| ((*token)->str[*i] == '\"' && (*token)->status == DQUOTE))
	{
		(*token)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
		return (false);
}

int	remove_quotes(t_token **token)
{
	char	*new_line;
	int		i;
	int		j;

	i = 0;
	j = 0;
	new_line = malloc(sizeof(char) * count_len((*token)->str, i, i));
	if (!new_line)
		return (1);
	while ((*token)->str[i])
	{
		if (quote_and_status_default(token, i) == true)
		{
			change_status_quote(token, &i);
			continue ;
		}
		else if (back_status_to_default(token, &i) == true)
			continue ;
		new_line[j++] = (*token)->str[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token)->str);
	(*token)->str = new_line;
	(*token)->join = true;
	return (0);
}
