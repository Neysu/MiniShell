/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   open_files.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/10 23:18:13 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/05 13:50:35 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	**add_args(char **cmd, char **new_args)
{
	char	**new;
	int		i;
	int		j;

	new = ft_calloc(sizeof(char *), ft_arrlen(cmd) + ft_arrlen(new_args));
	if (!new)
		return (NULL);
	i = 0;
	while (cmd[i])
		new[i] = ft_strdup(cmd[i]);
	j = 1;
	while (new_args[j])
	{
		new[i] = new_args[j];
		i++;
		j++;
	}
	ft_free_arr(cmd);
	return (new);
}

void	ft_closefds(t_cmd *cmd_data)
{
	t_cmd	*current;

	current = cmd_data;
	while (current)
	{
		if (current->fd >= 0)
			close(current->fd);
		current = current->next;
	}
}
