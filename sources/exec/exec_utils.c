/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec_utils.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:59 by elliot            #+#    #+#             */
/*   Updated: 2025/03/26 02:30:35 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stddef.h>

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
	while (ft_strncmp(envp->var, "PATH=", 5) && envp->next)
		envp = envp->next;
	if (!envp)
		return (NULL);
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

size_t	cmd_size(t_token *lst)
{
	t_token	*current;
	size_t	i;

	i = 0;
	current = lst;
	while (current && current->type == WORD)
	{
		current = current->next;
		i++;
	}
	return (i);
}

char	**get_cmd(t_token *lst)
{
	t_token	*current;
	char	**cmd;
	size_t		i;

	i = 0;
	cmd = ft_calloc(sizeof(char *), cmd_size(lst) + 1);
	current = lst;
	while (current && current->type == WORD)
	{
		cmd[i] = ft_strdup(current->str);
		i++;
		current = current->next;
	}
	cmd[i] = NULL;
	return (cmd);
}
