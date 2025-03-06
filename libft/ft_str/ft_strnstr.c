/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_strnstr.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/16 17:13:57 by egibeaux          #+#    #+#             */
/*   Updated: 2025/02/26 22:35:22 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

char	*ft_strnstr(const char *big, const char *little, size_t len)
{
	char	*bigstr;
	size_t	i;
	size_t	j;

	i = 0;
	bigstr = (char *)big;
	if ((char)little[0] == '\0')
		return (bigstr);
	while (bigstr[i] && i < len)
	{
		j = 0;
		while (bigstr[i + j] == little[j] && bigstr[i + j]
			&& (i + j) < len)
			j++;
		if (little[j] == '\0')
			return (&bigstr[i]);
		i++;
	}
	return (NULL);
}
