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
	while (current && (lst->type == WORD || lst ->type == ENV))
	{
		current = current->next;
		i++;
	}
	printf("%zu\n", i);
	return (i);
}

char	**env_to_str(t_envp *envp)
{
	char	**env;
	t_envp	*current;
	int		i;

	i = 0;
	env = ft_calloc(sizeof(char *), ft_envsize(envp));
	current = envp;
	while (current->next)
	{
		env[i] = ft_strdup(current->var);
		i++;
		current = current->next;
	}
	return (env);
}

char	*get_env_var(char *s, t_envp *envp)
{
	t_envp	*current;
	char	*var;

	var = NULL;
	current = envp;
	while (current)
	{
		if (!ft_strncmp(current->var, s, ft_strlen(s)))
		{
			var = ft_strdup(current->var + ft_strpos(current->var, '=') + 1);
			return (var);
		}
		current = current->next;
	}
	return (var);
}

void	get_cmd(t_token *lst, t_data *data)
{
	t_cmd	*current;
	size_t		i;

	i = 0;
	current = data->cmd_data;
	while (lst)
	{
		current = ft_calloc(sizeof(t_cmd), 1);
		if (lst->type == WORD || lst->type == ENV)
			current->cmd = ft_calloc(sizeof(char *), 5000);
		while (lst && (lst->type == WORD || lst ->type == ENV))
		{
			if (lst->type == ENV)
				current->cmd[i] = get_env_var(lst->str + 1, data->envp);
			else
				current->cmd[i] = ft_strdup(lst->str);
			i++;
			lst = lst->next;
		}
		current->cmd[i++] = NULL;
		current = current->next;
		lst = lst->next;
	}
}

