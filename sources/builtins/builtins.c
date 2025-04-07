/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:20:54 by elliot            #+#    #+#             */
/*   Updated: 2025/04/07 01:13:21 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		exec_buitlins(char *line, t_data *data)
{
	if (!ft_strncmp(line, "env", 3))
		print_env(data->envp);
	if (!ft_strncmp(line, "pwd", 3))
		print_pwd(line);
	if (!ft_strncmp(line, "echo", 4))
		ft_echo(line, data);
	if (!ft_strncmp(line, "unset", 5))
		ft_unset(line, data->envp);
	if (!ft_strncmp(line, "cd", 2))
		change_dirs(data->envp, line);
	if (!ft_strncmp(line, "export", 6))
		ft_export(line, data->envp);
	if (!ft_strncmp(line, "exit", 4))
		ft_exit(line, data);
	return (0);
}

