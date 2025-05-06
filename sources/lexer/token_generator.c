/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   token_generator.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/29 12:25:21 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/06 13:04:59 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	save_word(t_token **token_list, char *str, int index, int start)
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
	lst_addback_token(token_list, \
		lst_new_token(word, ft_strdup(word), WORD, DEFAULT));
	return (0);
}

static int	save_separator(t_token **token_list, char *str, int index, int type)
{
	char	*sep;
	int		i;

	i = 0;
	if (type == APPEND || type == HEREDOC)
	{
		sep = malloc(sizeof(char) * 3);
		if (!sep)
			return (1);
		while (i < 2)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_addback_token(token_list, lst_new_token(sep, NULL, type, DEFAULT));
	}
	else
	{
		sep = malloc(sizeof(char) * 2);
		if (!sep)
			return (1);
		while (i < 1)
			sep[i++] = str[index++];
		sep[i] = '\0';
		lst_addback_token(token_list, lst_new_token(sep, NULL, type, DEFAULT));
	}
	return (0);
}

static int	save_word_or_sep(int *i, char *str, int start, t_data *data)
{
	int	type;

	type = is_separator(str, (*i));
	if (type)
	{
		if ((*i) != 0 && is_separator(str, (*i) - 1) == 0)
			save_word(&data->token, str, (*i), start);
		if (type == PIPE || type == REDIRECT_IN || type == REDIRECT_OUT
			|| type == APPEND || type == HEREDOC || type == END)
		{
			save_separator(&data->token, str, (*i), type);
			if (type == APPEND || type == HEREDOC)
				(*i)++;
		}
		start = (*i) + 1;
	}
	return (start);
}

int	token_generator(t_data *data, char *str)
{
	int	i;
	int	str_len;
	int	start;
	int	status;

	i = -1;
	start = 0;
	str_len = ft_strlen(str);
	status = DEFAULT;
	while (++i <= str_len)
	{
		status = check_quotes(status, str, i);
		if (status == DEFAULT)
			start = save_word_or_sep(&i, str, start, data);
	}
	if (status != DEFAULT)
	{
		if (status == DQUOTE)
			error_message("Unclosed quotation mark detected", "\"", true);
		else if (status == SQUOTE)
			error_message("Unclosed quotation mark detected", "\'", true);
		error_message("syntax error", "unexpected end of file", false);
		return (1);
	}
	return (0);
}
