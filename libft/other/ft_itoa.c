/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_itoa.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/21 16:18:06 by elliot            #+#    #+#             */
/*   Updated: 2025/01/19 17:45:10 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

static	int	ft_intlen(int n)
{
	int	i;

	i = 0;
	if (n == 0)
		i++;
	if (n == -2147483648)
	{
		return (11);
	}
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

static	char	*ft_intostr(char *s, int n, int len)
{
	int	hope;

	hope = 0;
	if (n < 0)
	{
		n *= -1;
		hope = 1;
	}
	s[len] = '\0';
	while (len-- && n >= 0)
	{
		s[len] = (n % 10) + '0';
		n /= 10;
	}
	if (hope == 1)
		s[0] = '-';
	return (s);
}

char	*ft_itoa(int n)
{
	int		i;
	int		len;
	char	*str;

	i = n;
	len = ft_intlen(i);
	if (i == -2147483648)
		str = ft_strdup("-2147483648");
	else
	{
		str = (char *) malloc((len + 1) * sizeof(char));
		if (!str)
			return (NULL);
		ft_intostr(str, i, len);
	}
	return (str);
}
