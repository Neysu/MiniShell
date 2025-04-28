/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_io.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:52:49 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/28 20:12:30 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static void	open_infile(t_cmd *cmd, char *file)
{
	if (!remove_old_file_ref(cmd, true))
		return ;
	cmd->infile = ft_strdup(file);
	if (cmd->infile && cmd->infile[0] == '\0')
	{
		error_message(cmd->infile, "ambiguous redirect", false);
		return ;
	}
	cmd->fd_in = open(cmd->infile, O_RDONLY);
	if (cmd->fd_in == -1)
		printf("File dont opened: %d\n", cmd->fd_in);
}

static void	open_outfile(t_cmd *cmd, char *file)
{
	if (!remove_old_file_ref(cmd, false))
		return ;
	cmd->outfile = ft_strdup(file);
	if (cmd->outfile && cmd->outfile[0] == '\0')
	{
		error_message(cmd->infile, "ambiguous redirect", false);
		return ;
	}
	cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (cmd->fd_out == -1)
		printf("File dont opened: %d\n", cmd->fd_in);
}

void	set_outfile(t_token **token, t_cmd **last_cmd)
{
	t_token	*temp;
	t_cmd	*cmd;

	temp = *token;
	cmd = lst_last_cmd(*last_cmd);
	open_outfile(cmd, temp->next->str);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token = temp;
}

void	set_infile(t_token **token, t_cmd **last_cmd)
{
	t_cmd	*last;
	t_token	*temp;

	last = lst_last_cmd(*last_cmd);
	temp = *token;
	open_infile(last, temp->next->str);
	if (temp->next->next)
		temp = temp->next->next;
	else
		temp = temp->next;
	*token = temp;
}
