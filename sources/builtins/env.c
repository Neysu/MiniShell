/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:16:23 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/18 23:16:16 by egibeaux         ###   ########.fr       */
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
