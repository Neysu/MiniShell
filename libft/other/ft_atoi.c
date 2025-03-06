/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_atoi.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/10/15 16:14:30 by elliot            #+#    #+#             */
/*   Updated: 2025/01/19 17:45:10 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../libft.h"

int	ft_atoi(const char *str)
{
	int	i;
	int	check;
	int	result;
	int	sign;

	sign = 1;
	check = 0;
	result = 0;
	i = 0;
	while (str[i] == '\t' || str[i] == '\n' || str[i] == '\v'
		|| str[i] == '\f' || str[i] == '\r' || str[i] == ' ')
		i++;
	while ((str[i] == '+' || str[i] == '-') && check < 1)
	{
		if (str[i] == '-')
			sign *= -1;
		check++;
		i++;
	}
	while (str[i] >= '0' && str[i] <= '9' && check <= 1)
	{
		result = result * 10 + (str[i] - '0');
		i++;
	}
	return (result * sign);
}
