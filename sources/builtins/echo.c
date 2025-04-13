/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:15:41 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/13 18:28:57 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_echo(char *line, t_data *data)
{
	char	**tab;
	int		i;
	bool	new_line;

	i = 1;
	(void)line;
	new_line = true;
	tab = data->cmd->cmd;
	while (tab[i] && !ft_strncmp(tab[i], "-n", -1))
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
	return (0);
}

