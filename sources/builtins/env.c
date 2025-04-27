/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:16:23 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/27 16:57:51 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		print_env(t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current)
	{
		if (current->var[0])
			ft_putendl_fd(current->var, 1);
		current = current->next;
	}
	return (0);
}

// int		print_env2(char **envp)
// {
// 	int i = 0;
// 	while (envp[i])
// 	{
// 		if (envp[i])
// 			ft_putendl_fd(envp[i], 1);
// 		i++;
// 	}
// 	return (0);
// }
