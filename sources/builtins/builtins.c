/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:20:54 by elliot            #+#    #+#             */
/*   Updated: 2025/04/07 17:40:35 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		exec_buitlins(char *line, t_data *data)
{
	if (!ft_strncmp(line, "env", -1))
		print_env(data->envp);
	if (!ft_strncmp(line, "pwd", -1))
		print_pwd(line);
	if (!ft_strncmp(line, "echo", -1))
		ft_echo(line, data);
	if (!ft_strncmp(line, "unset", -1))
		ft_unset(line, data->envp);
	if (!ft_strncmp(line, "cd", -1))
		change_dirs(data->envp, data->cmd);
	if (!ft_strncmp(line, "export", -1))
		ft_export(line, data->envp);
	if (!ft_strncmp(line, "exit", -1))
		ft_exit(line, data);
	return (0);
}

