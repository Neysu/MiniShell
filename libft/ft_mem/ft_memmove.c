/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_memmove.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 14:08:04 by egibeaux          #+#    #+#             */
/*   Updated: 2025/01/19 17:51:03 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "../libft.h"

void	*ft_memmove(void *dest, const void *src, size_t n)
{
	unsigned char	*dst;
	unsigned char	*sorc;

	sorc = (unsigned char *)src;
	dst = (unsigned char *)dest;
	if (!dest && !src)
		return (NULL);
	if (src > dest)
	{
		while (n--)
			*dst++ = *sorc++;
	}
	else
	{
		while (n--)
			dst[n] = sorc[n];
	}
	return (dest);
}
