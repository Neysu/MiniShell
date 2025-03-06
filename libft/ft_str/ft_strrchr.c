/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strrchr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 11:11:01 by egibeaux          #+#    #+#             */
/*   Updated: 2025/02/02 21:50:21 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strrchr(const char *s, int c)
{
	char	*str;
	char	*ptr;

	ptr = NULL;
	str = (char *)s;
	if (!*s)
		return (NULL);
	while (*str)
	{
		if (*str == (unsigned char) c)
			ptr = str;
		str++;
	}
	if ((char)c == '\0')
		return (str);
	return (ptr);
}
