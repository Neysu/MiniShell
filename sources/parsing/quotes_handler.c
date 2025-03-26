/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   quotes_handler.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/25 19:40:41 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/26 13:00:10 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	count_len(char *str, int count, int i)
{
	int	status;

	status = 0;
	while (str[i])
	{
		if ((str[i] == '\"' ||str[i] == '\'') && status == DEFAULT)
		{
			if (str[i] == '\"')
				status = DQUOTE;
			if (str[i] == '\'')
				status = SQUOTE;
			i++;
			continue;
		}
		else if ((str[i] == '\"' && status == DQUOTE) ||(str[i] == '\'' && status == SQUOTE))
		{
			status = DEFAULT;
			i++;
			continue;
		}
		count++;
		i++;
	}
	return (count +1);
}

bool	quote_and_status_default(t_token **token, int i)
{
	if (((*token)->str[i] == '\"' || (*token)->str[i] == '\'')
		&& (*token)->status == DEFAULT)
		return (true);
	else
		return (false);
}

void	change_status_quote(t_token **token, int *i)
{
	if ((*token)->str[*i] == '\"')
		(*token)->status = DQUOTE;
	if ((*token)->str[*i] == '\'')
		(*token)->status = SQUOTE;
	(*i)++;
}

bool	back_status_to_default(t_token **token, int *i)
{
	if (((*token)->str[*i] == '\"' && (*token)->status == DQUOTE)
		|| ((*token)->str[*i] == '\'' && (*token)->status == SQUOTE))
	{
		(*token)->status = DEFAULT;
		(*i)++;
		return (true);
	}
	else
	{
		return (false);
	}
}



int remove_quotes(t_token **token)
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
			continue;
		}
		else if (back_status_to_default(token, &i) == true)
			continue;
		new_line[j++] = (*token)->str[i++];
	}
	new_line[j] = '\0';
	free_ptr((*token)->str);
	(*token)->str = new_line;
	return (0);
}

bool	quotes_in_str(char *str)
{
	int	i;

	i = 0;
	while(str[i])
	{
		if (str[i] == '\'' ||str[i] == '\"')
			return (true);
		i++;
	}
	return (false);
}

void	quotes_handler(t_data *data)
{
	t_token	*temp;

	temp = data->token;
	while (temp)
	{
		if(quotes_in_str(temp->str) && (!temp->prev || (temp->prev && temp->prev->type != HEREDOC)))
			remove_quotes(&temp);
		temp = temp->next;
	}
}
