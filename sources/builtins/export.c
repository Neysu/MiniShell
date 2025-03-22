/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   export.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/19 02:27:58 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/20 22:34:33 by egibeaux         ###   ########.fr       */
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

char	*get_var(char *var)
{
	char	*dest;
	int		i;

	i = 0;
	dest = ft_calloc(sizeof(char), ft_strlen(var));
	while (var[i] && var[i] != '=')
	{
		if (ft_isalpha(var[i]))
			dest[i] = var[i];
		else if (var[i] != '\'' && var[i] != '\"')
			return (NULL);
		i++;
	}
	while (var[i])
	{
		if (var[i] != 34 && var[i] != 39)
			dest[i] = var[i];
		i++;
	}
	dest[i++] = '\0';
	return (dest);
}

int		modify_var(char *var, t_envp *envp_data)
{
	t_envp	*current;

	current = envp_data;
	while (current)
	{
		if (!ft_strncmp(current->var, var, ft_strpos(var, '=') - 1))
		{
			free(current->var);
			current->var = NULL;
			current->var = ft_strdup(var);
			return (1);
		}
		current = current->next;
	}
	return (0);
}

int	ft_export(char *line, t_envp *envp_data)
{
	char    **args;
	char	*str;
	char	*var;
	int		i;

	args = ft_split(line, ' ');
	if (ft_arrlen(args) < 2)
		put_env(envp_data);
	i = 1;
	while (args[i])
	{
		str = ft_strdup(args[i]);
		if (!ft_strchr(str, '='))
			return (ft_putendl_fd("ERROR", 2), 1);
		if (modify_var(str, envp_data) == 0)
		{
			var = get_var(str);
			if (!var)
				return (1);
			ft_lstadd_back_env(&envp_data, var);
			free(var);
		}
		free(str);
		i++;
	}
	ft_free_arr(args);
	return (0);
}
