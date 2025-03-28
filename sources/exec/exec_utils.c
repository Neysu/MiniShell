/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:59 by elliot            #+#    #+#             */
/*   Updated: 2025/03/09 11:59:57 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*findcmd(t_cmd *cmd_data, t_envp *envp)
{
	int		i;
	char	*ret;
	char	*tmp;
	char	**path;

	i = 0;
	ret = NULL;
	if (!access(cmd_data->cmd[0], X_OK))
		return (cmd_data->cmd[0]);
	while (ft_strncmp(envp->var, "PATH=", 5) && envp)
		envp = envp->next;
	path = ft_split(envp->var + 5, ':');
	i = 0;
	while (path[i])
	{
		tmp = ft_strsep(path[i], cmd_data->cmd[0], '/');
		if (!access(tmp, X_OK))
			ret = ft_strdup(tmp);
		free(tmp);
		i++;
	}
	ft_free_arr(path);
	return (ret);
}
