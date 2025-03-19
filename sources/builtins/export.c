/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:27:58 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/19 02:30:24 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	put_env(t_envp *envp_data)
{
	t_envp *current;

	current = envp_data;
	while (current)
	{
		ft_putstr_fd("declare -x", 1);
		ft_putendl_fd(current->var, 1);
		current = current->next;
	}
}

char	*varname(char *var)
{
	char	*dest;
	int		i;

	i = 0;
	if (!ft_strchr(var, '='))
		return (NULL);
	while (var[i] && var[i] != '=')
	{
		if (!ft_isalpha(var[i]))
			return (NULL);
		i++;
	}
	dest = ft_calloc(sizeof(char), i + 1);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		dest[i] = var[i];
		i++;
	}
	dest[i] = '\0';
	return (dest);
}

int	ft_export(char *line, t_envp *envp_data)
{
	char    **args;

	args = ft_split(line, ' ');
	if (ft_arrlen(args) < 2)
		put_env(envp_data);
    ft_printf("%s\n", varname(args[1]));
	return (0);
}
