/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:06:59 by elliot            #+#    #+#             */
/*   Updated: 2025/03/17 22:09:50 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <stdbool.h>
#include <stddef.h>

int		print_env(t_envp *envp)
{
	t_envp	*current;

	current = envp;
	while (current->next)
	{
		if (current->var[0])
			ft_putendl_fd(current->var, 1);
		current = current->next;
	}
	return (0);
}

int		ft_echo(char *line)
{
	char	**tab;
	int		i;
	bool	new_line;

	i = 1;
	new_line = true;
	tab = ft_split(line, ' ');
	while (!ft_strncmp(tab[i], "-n", 2) && tab[i])
	{
		new_line = false;
		i++;
	}
	while (tab[i])
	{
		ft_putstr_fd(tab[i], 1);
		ft_putchar_fd(' ', 2);
		i++;
	}
	if (new_line)
		ft_putchar_fd('\n', 1);
	return (0);
}

int		print_pwd(char *line)
{
	char	*buffer;
	char	*pwd;
	size_t	size;

	(void)line;
	size = PATH_MAX_LEN;
	buffer = ft_calloc(sizeof(char), PATH_MAX_LEN);
	pwd = getcwd(buffer, size);
	if (!pwd)
		return (1);
	ft_putendl_fd(pwd, 1);
	free(pwd);
	return (0);
}

int		ft_unset(char *line, t_envp *envp_data)
{
	int		i;
	size_t	len;
	t_envp	*current;
	char	**args;

	i = 1;
	args = ft_split(line, ' ');
	if (ft_arrlen(args) < 2)
		return (ft_putendl_fd(UNSETARGS, 2), 1);
	while (args[i])
	{
		len = ft_strlen(args[i]);
		current = envp_data;
		while (current->next)
		{
			if (!ft_strncmp(current->var, args[i], len))
				ft_bzero(current->var, ft_strlen(current->var));
			current = current->next;
		}
		i++;
	}
	return (0);
}

int		change_dirs(t_envp *envp, char *line)
{
	char	**args;
	char	*path;

	(void)envp;
	path = ft_calloc(sizeof(char), PATH_MAX_LEN);
	getcwd(path, PATH_MAX_LEN);
	args = ft_split(line, ' ');
	if (ft_arrlen(args) != 2)
		return (ft_putendl_fd("Too much args", 2), 1);
	path = ft_strsep(path, args[1], '/');
	if (chdir((const char *)path) == -1)
		return (perror(path), 1);
	return (0);
}