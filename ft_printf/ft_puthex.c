/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_puthex.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/11/05 19:05:33 by egibeaux          #+#    #+#             */
/*   Updated: 2024/11/05 19:11:12 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

void	ft_toptr(unsigned long long num)
{
	if (num >= 16)
	{
		ft_toptr(num / 16);
		ft_toptr(num % 16);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
			ft_putchar_fd((num - 10 + 'a'), 1);
	}
}

void	ft_tohex(unsigned int num, char c)
{
	if (num >= 16)
	{
		ft_tohex(num / 16, c);
		ft_tohex(num % 16, c);
	}
	else
	{
		if (num <= 9)
			ft_putchar_fd((num + '0'), 1);
		else
		{
			if (c == 'x')
				ft_putchar_fd((num - 10 + 'a'), 1);
			if (c == 'X')
				ft_putchar_fd((num - 10 + 'A'), 1);
		}
	}
}

int	ft_puthex(unsigned int n, char c)
{
	int	nbr;

	nbr = n;
	if (n == 0)
		write (1, "0", 1);
	else
		ft_tohex(n, c);
	return (ft_hexlen(nbr));
}

int	ft_putptr(unsigned long long n)
{
	int	print_length;

	print_length = 0;
	if (n > 0)
		print_length += write(1, "0x", 2);
	if (n == 0)
		print_length += write(1, "(nil)", 5);
	else
	{
		ft_toptr(n);
		print_length += ft_ptrlen(n);
	}
	return (print_length);
}
