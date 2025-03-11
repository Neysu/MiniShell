/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/11 17:52:05 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *line)
{
	if (!ft_strncmp(line, "echo", 4))
		return (1);
	if (!ft_strncmp(line, "cd", 2))
		return (1);
	if (!ft_strncmp(line, "pwd", 3))
		return (1);
	if (!ft_strncmp(line, "export", 6))
		return (1);
	if (!ft_strncmp(line, "unset", 5))
		return (1);
	if (!ft_strncmp(line, "env", 3))
		return (1);
	if (!ft_strncmp(line, "exit", 4))
		return (1);
	return (0);
}

t_cmd	*parse_cmd(char *line)
{
	t_cmd	*cmd_data;
	char	**cmd;

	cmd_data = ft_calloc(sizeof(t_cmd), 1);
	cmd = ft_split(line, ' ');
	cmd_data->cmd = cmd;
	return (cmd_data);
}