/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/07 03:22:17 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_envp	*ft_lstnew_env(char *envp)
{
	t_envp	*var;

	var = malloc(sizeof(t_envp));
	if (!var)
		return (NULL);
	var->env = ft_strdup(envp);
	var->next = NULL;
	return (var);
}

void	ft_lstadd_back(t_envp **lst, char *envp)
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
		printf("%s\n", current->env);
		while (current->next)
			current = current->next;
		current->next = new;
	}
}

t_envp	*get_env(char **envp)
{
	int		i;
	t_envp	*env;

	i = 0;
	while (envp[i])
	{
		ft_lstadd_back(&env, envp[i]);
		i++;
	}
	return (env);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_envp	*env;

	(void)argc;
	(void)argv;
	(void)line;
	env	= get_env(envp);
	while (env)
	{
		ft_putendl_fd(env->env, 1);
		env = env->next;
	}
	//while (env)
	//{
	//	ft_putendl_fd(env->env, 1);
	//	env = env->next;
	//}
	//while (1)
	//{
	//	line = readline("MINISHELL > ");
	//	system(line);
	//}
	return (0);
}
