/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_putubnr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 18:37:40 by egibeaux          #+#    #+#             */
/*   Updated: 2024/11/05 21:38:01 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_intlen(long n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n < 0)
	{
		n *= -1;
		i++;
	}
	while (n)
	{
		n /= 10;
		i++;
	}
	return (i);
}

static void	ft_putnbr(unsigned int n)
{
	if (n > 9)
	{
		ft_putunbr(n / 10);
	}
	ft_putchar((n % 10) + '0');
}

int	ft_putunbr(unsigned int n)
{
	unsigned int	nbr;

	nbr = n;
	ft_putnbr(nbr);
	return (ft_intlen(nbr));
}

int	ft_putn(int n)
{
	int	nbr;

	nbr = n;
	ft_putnbr_fd(nbr, 1);
	return (ft_intlen(nbr));
}
