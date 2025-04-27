/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:20:54 by elliot            #+#    #+#             */
/*   Updated: 2025/04/27 16:59:03 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int		exec_buitlins(t_data *data, t_cmd *cmd)
{
	int	ret;

	ret = CMD_NOT_FOUND;
	if (!ft_strncmp(cmd->cmd[0], "env", -1))
		ret = print_env(data->envp);
	if (!ft_strncmp(cmd->cmd[0], "pwd", -1))
		ret = print_pwd(cmd->cmd[0]);
	if (!ft_strncmp(cmd->cmd[0], "echo", -1))
		ret = ft_echo(cmd->cmd[0], data);
	if (!ft_strncmp(cmd->cmd[0], "unset", -1))
		ret = ft_unset(cmd->cmd[0], data->envp);
	if (!ft_strncmp(cmd->cmd[0], "cd", -1))
		ret = change_dirs(data->envp, data->cmd);
	if (!ft_strncmp(cmd->cmd[0], "export", -1))
		ret = ft_export(cmd->cmd[0], data->envp);
	if (!ft_strncmp(cmd->cmd[0], "exit", -1))
		ret = ft_exit(cmd->cmd[0], data);
	return (ret);
}

