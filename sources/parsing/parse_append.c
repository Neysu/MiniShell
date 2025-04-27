/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_append.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 12:00:19 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/25 12:24:51 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	open_outfile_append(t_cmd *cmd, char *file, char *var_filename)
{
	if (!remove_old_file_ref(cmd, false))
		return ;
	cmd->outfile = ft_strdup(file);
	if (cmd->outfile && cmd->outfile[0] == '\0' && var_filename)
	{
		errmsg_cmd(var_filename, NULL, "ambiguous redirect", false);
		return ;
	}
	cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_APPEND, 0664);
	if (cmd->fd_out == -1)
		errmsg_cmd(cmd->outfile, NULL, strerror(errno), false);
}

void	parse_append(t_cmd **last_cmd, t_token **token_lst)
{
	t_token		*temp;
	t_cmd	*cmd;

	temp = *token_lst;
	cmd = lst_last_cmd(*last_cmd);
	open_outfile_append(cmd, temp->next->str, temp->next->str_backup);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token_lst = temp;
}
