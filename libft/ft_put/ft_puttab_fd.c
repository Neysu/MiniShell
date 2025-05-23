/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puttab_fd.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/01/31 00:30:38 by egibeaux          #+#    #+#             */
/*   Updated: 2025/02/10 14:37:38 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	ft_puttab_fd(char **tab, int fd)
{
	int		i;

	i = 0;
	while (tab[i])
	{
		ft_putstr_fd(tab[i], fd);
		i++;
	}
}
