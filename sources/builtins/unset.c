/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   unset.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:14:33 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/18 20:15:00 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_unset(char *line, t_envp *envp_data)
{
	int		i;
	size_t	len;
	t_envp	*current;
	char	**args;

	i = 1;
	args = ft_split(line, ' ');
	if (ft_arrlen(args) < 2)
		return (ft_putendl_fd(UNSETARGS, 2), 1);
	while (args[i])
	{
		len = ft_strlen(args[i]);
		current = envp_data;
		while (current->next)
		{
			if (!ft_strncmp(current->var, args[i], len))
				ft_bzero(current->var, ft_strlen(current->var));
			current = current->next;
		}
		i++;
	}
	return (0);
}
