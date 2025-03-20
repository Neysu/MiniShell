/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:27:58 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/20 13:38:43 by elliot           ###   ########.fr       */
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
		if (!ft_isalpha(var[i]) && var[i] != 34 && var[i] != 39)
			return (NULL);
		i++;
	}
	dest = ft_calloc(sizeof(char), i + 1);
	i = 0;
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]))
			dest[i] = var[i];
		i++;
	}
	dest[i++] = '\0';
	return (dest);
}


char    *get_var_content(char *var)
{
	char	*dest;
	int		i;
	int		j;

	i = 0;
	j = 0;
	while (var[i] && var[i] != '=')
		i++;
	if (var[i] == '=')
		i++;
	if (!var[i])
		return (NULL);
	dest = ft_calloc(sizeof(char), ft_strlen(var + i));
	while (var[i])
	{
		if (var[i] != 34 && var[i] != 39)
			dest[j++] = var[i];
		i++;
	}
	return (dest);
}

char	*get_var(char *var)
{
	char	*name;
	char	*content;
	char	*ret;

	name = varname(var);
	if (!name)
		return (NULL);
	content = get_var_content(var);
	if (!content)
		return (ft_strjoin(name, "="));
	ret = ft_strsep(name, content, '=');
	(free(name), free(content));
	return (ret);
}

int	ft_export(char *line, t_envp *envp_data)
{
	char    **args;
	char	*var;
	int		i;

	args = ft_split(line, ' ');
	if (ft_arrlen(args) < 2)
		put_env(envp_data);
	i = 1;
	while (args[i])
	{
		var = get_var(args[i]);
		if (!var)
			i++;
		else
		{
			ft_lstadd_back_env(&envp_data, var);
			i++;
		}
		free(var);
	}
	return (0);
}
