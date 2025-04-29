/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_split.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/25 01:40:14 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/29 15:56:34 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"
#include <stdlib.h>
#include <stdbool.h>

static void	ft_free(char **tab, size_t allocated)
{
	size_t	i;

	if(!tab)
		return ;
	i = 0;
	while (i < allocated)
	{
		free(tab[i]);
		i++;
	}
	free(tab);
}

static size_t	ft_count_words(const char *s, char c)
{
	size_t	count;
	size_t	i;

	count = 0;
	i = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (s[i])
		{
			count++;
			while (s[i] && s[i] != c)
				i++;
		}
	}
	return (count);
}

static bool	ft_alloc(char **tab, const char *s, char c)
{
	size_t	i;
	size_t	j;
	size_t	start;

	i = 0;
	j = 0;
	while (s[i])
	{
		while (s[i] == c)
			i++;
		if (!s[i])
			break ;
		start = i;
		while (s[i] && s[i] != c)
			i++;
		tab[j] = ft_substr(s, start, i - start);
		if (!tab[j])
		{
			ft_free(tab, j);
			return (false);
		}
		j++;
	}
	tab[j] = NULL;
	return (true);
}

char	**ft_split(char const *s, char c)
{
	char	**tbl;
	size_t	word_count;

	if (!s)
		return (NULL);
	word_count = ft_count_words(s, c);
	tbl = ft_calloc(word_count + 1, sizeof(char *));
	if (!tbl)
		return (NULL);
	if (!ft_alloc(tbl, s, c))
		return (NULL);
	// if (!tbl[0] && word_count > 0)
	// {
	// 	free(tbl);
	// 	return (NULL);
	// }
	return (tbl);
}
