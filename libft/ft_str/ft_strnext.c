/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnext.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/26 22:38:28 by egibeaux          #+#    #+#             */
/*   Updated: 2025/02/26 22:39:22 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnext(const char *str, const char *ext, size_t len)
{
	char	*bigstr;
	size_t	i;
	size_t	j;

	i = 0;
	bigstr = (char *)str;
	if ((char)ext[0] == '\0')
		return (bigstr);
	while (bigstr[i] && i < len)
	{
		j = 0;
		while (bigstr[i + j] == ext[j] && bigstr[i + j]
			&& (i + j) < len)
			j++;
		if (ext[j] == '\0' && bigstr[i + j] == '\0')
			return (&bigstr[i]);
		i++;
	}
	return (NULL);
}
