/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/08 02:39:15 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*parse_cmd(char *line)
{
	t_cmd	*cmd_data;
	char	**cmd;

	cmd_data = ft_calloc(sizeof(t_cmd), 1);
	cmd = ft_split(line, ' ');
	cmd_data->cmd = cmd;
	return (cmd_data);
}