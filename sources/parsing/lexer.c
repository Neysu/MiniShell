/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/21 16:20:56 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/23 19:22:26 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	is_separator(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		return (SPACES);
	else if (str[i] == '|')
		return (PIPE);
	else if (str[i] == '<' && str[i + 1] == '<')
		return (HEREDOC);
	else if (str[i] == '>' && str[i + 1] == '>')
		return (APPEND);
	else if (str[i] == '>')
		return (REDIRECT_IN);
	else if (str[i] == '<')
		return (REDIRECT_OUT);
	else if (str[i] == '\0')
		return (END);
	return (0);
}

static int	check_quotes(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = SQUOTE;
	if (str[i] == '\"' && status == DEFAULT)
		status = DQUOTE;
	if (str[i] == '\'' && status == SQUOTE)
		status = DEFAULT;
	if (str[i] == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

t_token	*lst_new_token(char *str, int type, int status)
{
	t_token	*new_node;

	new_node = (t_token *)malloc(sizeof(t_token) * 1);
	if (!new_node)
		return (NULL);
	new_node->str = str;
	new_node->type = type;
	new_node->status = status;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	lst_addback_token(t_token **token_list, t_token *new_node)
{
	t_token *start;

	start = *token_list;
	if(start == NULL)
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

int	save_word(t_token **token_list, char *str, int index, int start)
{
	int		i;
	char	*word;

	i = 0;
	word = malloc(sizeof(char) * (index - start + 1));
	if (!word)
		return (1);
	while (start < index)
	{
		word[i] = str[start];
		i++;
		start++;
	}
	word[i] = '\0';
	lst_addback_token(token_list, lst_new_token(word, WORD, DEFAULT));
	return (0);
}

int	save_separator(t_token **token_list, char *str, int index, int type)
{
	char	*sep;
	int	i;

	i = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_addback_token(token_list, lst_new_token(sep, type, DEFAULT));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_addback_token(token_list, lst_new_token(sep, type, DEFAULT));
	}
	return (0);
}

int	token_generator(t_data *data, char *str)
{
	int	str_len;
	int	i;
	int	type;
	int	status;
	int	start;

	str_len = ft_strlen(str);
	i = -1;
	status = DEFAULT;
	start = 0;
	while (++i <= str_len)
	{
		status = check_quotes(status, str, i);
		if (status == DEFAULT)
		{
			type = is_separator(str, i);
			if (type)
			{
				if (i != 0 && is_separator(str, i - 1) == 0)
					save_word(&data->token, str, i, start);
				if (type == PIPE || type == REDIRECT_IN ||type == REDIRECT_OUT || type == APPEND || type == HEREDOC || type == END)
				{
					save_separator(&data->token, str, i, type);
					if (type == APPEND || type == HEREDOC)
						i++;
				}
				start = i + 1;
			}
		}
	}
	if (status != DEFAULT)
	{
		error_message("Unclosed quotation mark detected");
		return (1);
	}
	return (0);
}
