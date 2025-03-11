/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   builtins_utils.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/09 12:06:59 by elliot            #+#    #+#             */
/*   Updated: 2025/03/11 12:57:22 by elliot           ###   ########.fr       */
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
	//free(buffer);
	return (0);
}