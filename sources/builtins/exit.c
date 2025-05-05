/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exit.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 22:29:27 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/05 14:35:31 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	ft_exit(char *line, t_data *data)
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
		data->exit_code = (ret % 256);
	}
	free_str_tab(args);
	exit_shell(data, data->exit_code);
	return (2);
}
