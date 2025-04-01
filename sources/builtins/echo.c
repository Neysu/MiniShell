/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:15:41 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/29 23:22:18 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_env(char	*s, t_envp *envp_data)
{
	t_envp	*current;

	current = envp_data;
	while (current)
	{
		if (!ft_strncmp(current->var, s, ft_strlen(s)))
		{
			ft_putstr_fd(current->var, 1);
			return (0);
		}
		current = current->next;
	}
	return (1);
}

int	ft_echo(char *line, t_data *data)
{
	char	**tab;
	int		i;
	bool	new_line;

	i = 1;
	(void)line;
	new_line = true;
	tab = data->cmd->args;
	while (tab[i] && !ft_strncmp(tab[i], "-n", 2))
	{
		new_line = false;
		i++;
	}
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putchar_fd(' ', 1);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	ft_free_arr(tab);
	return (0);
}

