/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:15:16 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/28 20:54:28 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void 	update_status(t_token **token, char c)
{
	if (c == '\'' && (*token)->type == DEFAULT)
		(*token)->type = SQUOTE;
	else if (c == '\"' && (*token)->type == DEFAULT)
		(*token)->type = DQUOTE;
	else if (c == '\'' && (*token)->type == SQUOTE)
		(*token)->type = DEFAULT;
	else if (c == '\"' && (*token)->type == DQUOTE)
		(*token)->type = DEFAULT;
}

bool	char_is_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

bool	between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\"' || str[i + 1] == '\'')
			return (true);
		else
			return (false);
	}
	return (false);
}

bool	is_var_valid(char c)
{
	if (ft_isalnum(c) == 0 || c == '_')
		return (false);
	else
		return (true);
}

int	var_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= 9) || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (is_var_valid(str[i]) == false)
			break;
		count++;
		i++;
	}
	return (count);
}

char	*search_name_var(char *str)
{
	char	*var;
	char	*tmp;
	int		len;
	int		start;
	int		i;

	i = 0;
	start  = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break;
		}
		i++;
	}
	len = var_len(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free(var);
	var = tmp;
	return (var);
}

char	*get_var_value(char *str)
{
	char	*name_var;

	name_var = search_name_var(str);
	return (name_var);
}

void	exchange_var(void)
{
	return ;
}

int	expand_variables(t_data *data, t_token **tokens)
{
	(void)data;
	t_token	*temp;
	int		i;

	temp = *tokens;
	while (temp)
	{
		if (temp->type == ENV)
		{
			i = 0;
			while (temp->str[i])
			{
				update_status(&temp, temp->str[i]);
				if (temp->str[i] == '$' && char_is_sep(temp->str[i + 1]) == false
					&& between_quotes(temp->str, i) == false
					&& (temp->status == DEFAULT || temp->status == DQUOTE))
					exchange_var();
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}
