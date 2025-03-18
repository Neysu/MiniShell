/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   echo.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:15:41 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/18 20:15:51 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_echo(char *line)
{
	char	**tab;
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	tab = ft_split(line, ' ');
	while (!ft_strncmp(tab[i], "-n", 2) && tab[i])
	{
		new_line = false;
		i++;
	}
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putchar_fd(' ', 2);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}