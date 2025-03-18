/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cd.c                                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:14:00 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/18 20:15:03 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
