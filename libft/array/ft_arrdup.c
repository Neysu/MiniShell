/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_arrdup.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/25 01:39:43 by egibeaux          #+#    #+#             */
/*   Updated: 2025/02/25 04:18:33 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stddef.h>

char	**ft_arrdup(char **src)
{
	size_t	i;
	char	**dest;
	size_t	arrlen;

	i = 0;
	if (!src)
		return (NULL);
	arrlen = ft_arrlen(src);
	dest = ft_calloc(sizeof(char *), arrlen + 1);
	while (src[i])
	{
		dest[i] = ft_strdup(src[i]);
		i++;
	}
	dest[i] = NULL;
	return (dest);
}
