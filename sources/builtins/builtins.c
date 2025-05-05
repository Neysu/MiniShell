/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:20:54 by elliot            #+#    #+#             */
/*   Updated: 2025/05/05 14:36:51 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	exec_buitlins(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->command, "cd", 3) == 0)
		ret = ft_cd(data, cmd->cmd);
	else if (ft_strncmp(cmd->command, "echo", 5) == 0)
		ret = ft_echo(data, cmd->cmd);
	else if (ft_strncmp(cmd->command, "env", 4) == 0)
		ret = print_env(data->env_list);
	else if (ft_strncmp(cmd->command, "export", 7) == 0)
		ret = ft_export(data, cmd->cmd);
	else if (ft_strncmp(cmd->command, "pwd", 4) == 0)
		ret = print_pwd(cmd->command);
	else if (ft_strncmp(cmd->command, "unset", 6) == 0)
		ret = ft_unset(data, cmd->cmd);
	else if (ft_strncmp(cmd->command, "exit", 5) == 0)
		ret = ft_exit(data->user_input, data);
	return (ret);
}
