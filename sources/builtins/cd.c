/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:14:00 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/21 21:32:09 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <unistd.h>

char	*find_home(t_envp *envp)
{
	t_envp	*current;
	char	*ret;
	char	**args;

	current = envp;
	while (current)
	{
		if (!ft_strncmp(current->var, "HOME", 4))
		{
			args = ft_split(current->var, '=');
			ret = ft_strdup(args[1]);
			ft_free_arr(args);
			return (ret);
		}
		current = current->next;
	}
	return (NULL);
}

char	*get_dirs(char *s)
{
	char	*ret;
	char	*path;

	path = ft_calloc(sizeof(char), PATH_MAX_LEN);
	getcwd(path, PATH_MAX_LEN);
	if (!ft_strncmp(s, "/", 1))
		ret = ft_strndup("/", 1);
	else
		ret = ft_strsep(path, s, '/');
	free(path);
	return (ret);
}

int		change_dirs(t_envp *envp, char *line)
{
	char	**args;
	char	*dir;
	char	*home;

	args = ft_split(line, ' ');
	if (ft_arrlen(args) > 2)
		return (ft_putendl_fd("Too much args", 2), 1);
	if (ft_arrlen(args) == 1)
	{
		home = find_home(envp);
		chdir(home);
		free(home);
	}
	else
	{
		dir = get_dirs(args[1]);
		if (chdir((const char *)dir) == -1)
			return (perror(dir), 1);
		free(dir);
	}
	ft_free_arr(args);
	return (0);
}
