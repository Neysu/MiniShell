/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:20:54 by elliot            #+#    #+#             */
/*   Updated: 2025/03/11 17:52:58 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_buitlins(char *line, t_envp *env_data)
{
	if (!ft_strncmp(line, "env", 3))
		print_env(env_data);
	if (!ft_strncmp(line, "pwd", 3))
		print_pwd(line);
	if (!ft_strncmp(line, "echo", 4))
		ft_echo(line);
	if (!ft_strncmp(line, "unset", 5))
		ft_unset(line, env_data);
	if (!ft_strncmp(line, "cd", 2))
		change_dirs(env_data, line);
	return (0);
}