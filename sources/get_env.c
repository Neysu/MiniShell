/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_env.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:33:00 by elliot            #+#    #+#             */
/*   Updated: 2025/03/25 23:17:34 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"
#include <stddef.h>

size_t	ft_envsize(t_envp *env)
{
	size_t	i;
	t_envp	*current;

	current = env;
	i = 0;
	while (current)
	{
		current = current->next;
		i++;
	}
	return (i);
}

t_envp	*ft_lstnew_env(char *envp)
{
	t_envp	*var;

	var = ft_calloc(sizeof(t_envp), 1);
	if (!var)
		return (NULL);
	var->var = ft_strdup(envp);
	var->next = NULL;
	return (var);
}

void	ft_lstadd_back_env(t_envp **lst, char *envp)
{
	t_envp	*new;
	t_envp	*current;

	new = ft_lstnew_env(envp);
	current = NULL;
	if (!new)
		return ;
	if (!*lst)
		*lst = new;
	else
	{
		current = *lst;
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

void	ft_free_env(t_envp *envp)
{
	t_envp	*tmp;

	while (envp)
	{
		tmp = envp->next;
		free(envp);
		envp = tmp;
	}
}

t_envp	*get_env(char **envp)
{
	int		i;
	t_envp	*env;

	i = 0;
	env = NULL;
	while (envp[i])
	{
		ft_lstadd_back_env(&env, envp[i]);
		i++;
	}
	return (env);
}
