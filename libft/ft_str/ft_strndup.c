/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strndup.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/02 21:09:06 by egibeaux          #+#    #+#             */
/*   Updated: 2025/02/24 15:49:47 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strndup(const char *s, size_t n)
{
	size_t		i;
	size_t		s_len;
	char		*dup;

	s_len = ft_strlen(s);
	if (n > s_len)
		n = s_len;
	dup = (char *)malloc((n + 1) * sizeof(char));
	if (!dup)
		return (NULL);
	i = 0;
	while (i < n)
		dup[i++] = *s++;
	dup[i] = '\0';
	return (dup);
}
