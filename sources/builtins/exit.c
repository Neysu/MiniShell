/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:29:27 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/29 23:21:52 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		ft_exit(char *line, t_data *data)
{
	char	**args;
	int		ret;

	args = ft_split(line, ' ');
	if (ft_arrlen(args) > 2)
	{
		ft_putendl_fd("minishell: exit: too many args", 2);
		return (1);
	}
	else if (ft_arrlen(args) == 2)
	{
		ft_putendl_fd("exit", 1);
		ret = ft_atoi(args[1]);
		if (ret < 1 || ret > 255)
			data->ret = 0;
		else
			data->ret = ret;
		data->work = false;
	}
	else
		exit(0);
	return (0);
}

