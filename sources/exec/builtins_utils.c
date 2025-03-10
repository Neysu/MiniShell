/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:06:59 by elliot            #+#    #+#             */
/*   Updated: 2025/03/10 03:10:48 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		print_env(t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current->next)
	{
		ft_putendl_fd(current->var, 1);
		current = current->next;
	}
	return (0);
}

int		ft_echo(char *line)
{
	
	return (0);
}

int		print_pwd(t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (ft_strncmp(current->var, "PWD", 3) && current->next)
		current = current->next;
	if (current->next)
		ft_putendl_fd(current->var + 4, 1);
	return (0);
}