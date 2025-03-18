/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pwd.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/18 20:16:45 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/18 20:16:58 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
