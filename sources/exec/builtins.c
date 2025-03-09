/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:20:54 by elliot            #+#    #+#             */
/*   Updated: 2025/03/09 13:24:19 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_buitlins(char *line, t_envp *env_data)
{
	if (!ft_strncmp(line, "env", 3))
		print_env(env_data);
	if (!ft_strncmp(line, "pwd", 3))
		print_pwd(env_data);
	return (0);
}