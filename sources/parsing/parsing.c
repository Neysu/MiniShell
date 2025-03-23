/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/18 13:24:59 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *line)
{
	if (!line)
		return (0);
	if (!ft_strncmp(line, "echo", 4))
		return (1);
	else if (!ft_strncmp(line, "cd", 2))
		return (1);
	else if (!ft_strncmp(line, "pwd", 3))
		return (1);
	else if (!ft_strncmp(line, "export", 6))
		return (1);
	else if (!ft_strncmp(line, "unset", 5))
		return (1);
	else if (!ft_strncmp(line, "env", 3))
		return (1);
	else if (!ft_strncmp(line, "exit", 4))
		return (1);
	return (0);
}

t_cmd	*parse_cmd(char *line)
{
	t_cmd	*cmd_data;
	char	**cmd;
	char	**red;
	char	**test;

	cmd_data = ft_calloc(sizeof(t_cmd), 1);
	red = ft_split(line, '<');
	if (ft_arrlen(red) == 2)
	{
		test = ft_split(red[1], ' ');
		cmd_data->file = ft_strndup(test[0], ft_strlen(test[0]));
		cmd = ft_split(red[0], ' ');
	}
	else
		cmd = ft_split(line, ' ');
	cmd_data->cmd = ft_arrdup(cmd);
	return (cmd_data);
}
