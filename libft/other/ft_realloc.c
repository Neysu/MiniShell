/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_realloc.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42lehavre.fr>   +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/03 18:36:19 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/03 18:47:27 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

void	*ft_realloc(void *ptr, size_t size)
{
	void	*new_ptr;

	new_ptr = NULL;
	if (!ptr)
	{
		ptr = malloc(size);
		if (!ptr)
			return (NULL);
	}
	else if (size == 0)
	{
		free(ptr);
		return (NULL);
	}
	else
	{
		new_ptr = malloc(size);
		ft_memcpy(new_ptr, ptr, size);
	}

	free(ptr);
	return (new_ptr);
}
