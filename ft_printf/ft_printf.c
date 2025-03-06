/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_printf.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/29 03:11:28 by elliot            #+#    #+#             */
/*   Updated: 2025/02/18 01:28:24 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_printf.h"

int	ft_put(char c, va_list *args)
{
	int		len;

	len = 0;
	if (c == 'd' || c == 'i')
		len += ft_putn(va_arg(*args, int));
	if (c == 'u')
		len += ft_putunbr(va_arg(*args, unsigned int));
	else if (c == 'c')
		len += ft_putchar(va_arg(*args, int));
	else if (c == 's')
		len += ft_putstr(va_arg(*args, char *));
	else if (c == 'X' || c == 'x')
		len += ft_puthex(va_arg(*args, int), c);
	else if (c == 'p')
		len += ft_putptr(va_arg(*args, unsigned long long));
	else if (c == '%')
		len += ft_putchar('%');
	return (len);
}

int	ft_printf(const char *str, ...)
{
	va_list	args;
	int		len;
	int		i;

	i = 0;
	len = 0;
	va_start(args, str);
	while (str[i])
	{
		if (str[i] == '%')
		{
			i++;
			len += ft_put(str[i++], &args);
		}
		else
		{
			len += ft_putchar(str[i]);
			i++;
		}
	}
	va_end(args);
	return (len);
}
