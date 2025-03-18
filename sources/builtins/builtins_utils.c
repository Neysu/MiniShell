/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:06:59 by elliot            #+#    #+#             */
/*   Updated: 2025/03/18 21:56:19 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	print_export(t_envp *envp_data)
{
	t_envp	*current;

	current = envp_data;
	while (current)
	{
		ft_putstr_fd("declare -x", 1);
	}
}

int		ft_export(t_envp *envp_data, char *line)
{
	char	**args;
	int		i;
	
	i = 0;
	args = ft_split(line, ' ');
	if (ft_arrlen(args) < 2)
	{
		print_env(envp_data);
		return (0);
	}
	return (0);
}
