/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:20:54 by elliot            #+#    #+#             */
/*   Updated: 2025/05/02 20:37:47 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		exec_buitlins(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (ft_strncmp(cmd->cmd[0], "cd", 3) == 0)
		ret = ft_cd(data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "echo", 5) == 0)
		ret = ft_echo(data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "env", 4) == 0)
		ret = print_env(data->env_list);
	else if (ft_strncmp(cmd->cmd[0], "export", 7) == 0)
		ret = ft_export(data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "pwd", 4) == 0)
		ret = print_pwd(cmd->cmd[0]);
	else if (ft_strncmp(cmd->cmd[0], "unset", 6) == 0)
		ret = ft_unset(data, cmd->cmd);
	else if (ft_strncmp(cmd->cmd[0], "exit", 5) == 0)
		ret = ft_exit(cmd->cmd[0], data);
	return (ret);
}

