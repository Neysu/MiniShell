/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:15:16 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/05 13:44:30 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	erase_var(t_token **token, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_len(str + index);
	new_str = (char *)malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i = i + var_len(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	free_ptr((*token)->str);
	(*token)->str = new_str;
	return (0);
}

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

char	*erase_and_replace(t_token **token, char *str,
							char *var_value, int index)
{
	char	*new_str;
	int		new_str_size;

	new_str_size = (ft_strlen(str) - var_len(str + index)
			+ ft_strlen(var_value));
	new_str = get_new_token_str(str, var_value, new_str_size, index);
	if (token && *token)
	{
		free_ptr((*token)->str);
		(*token)->str = new_str;
	}
	return (new_str);
}
