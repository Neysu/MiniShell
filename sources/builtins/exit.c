/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:29:27 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/07 03:23:02 by elliot           ###   ########.fr       */
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
			data->exit_code = 0;
		else
			data->exit_code = ret;
		data->work = false;
	}
	else
		data->work = false;
	return (0);
}

