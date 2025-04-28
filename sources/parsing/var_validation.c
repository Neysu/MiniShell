/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   var_validation.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:54:32 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/28 20:13:35 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
		if (str[i - 1] == '\'' || str[i + 1] == '\'' || str[0] == '\'')
			return (true);
		else
			return (false);
	}
	return (false);
}

bool	is_var_valid(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
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
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (is_var_valid(str[i]) == false)
			break ;
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
	start = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
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
