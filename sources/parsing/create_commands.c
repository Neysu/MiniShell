/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:44:03 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/04 19:06:06 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	prep_no_arg_commands(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->command)
	{
		if (!cmd->cmd)
		{
			cmd->cmd = malloc(sizeof * cmd->cmd * 2);
			cmd->cmd[0] = ft_strdup(cmd->command);
			cmd->cmd[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
}

bool	remove_old_file_ref(t_cmd *cmd, bool infile)
{
	if (infile == true && cmd->infile)
	{
		if (cmd->fd_in == -1 || (cmd->outfile && cmd->fd_out == -1))
			return (false);
		if (cmd->heredoc_delimiter != NULL)
		{
			free_ptr(cmd->heredoc_delimiter);
			cmd->heredoc_delimiter = NULL;
			unlink(cmd->infile);
		}
		free_ptr(cmd->infile);
		close(cmd->fd_in);
	}
	else if (infile == false && cmd->outfile)
	{
		if (cmd->fd_out == -1 || (cmd->infile && cmd->fd_in == -1))
			return (false);
		free_ptr(cmd->outfile);
		close(cmd->fd_out);
	}
	return (true);
}

void	create_commands(t_data *data, t_token *token)
{
	t_token	*temp;

	temp = token;
	if (temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_addback_cmd(&data->cmd, lst_new_cmd(false));
		if (temp->type == WORD || temp->type == ENV)
			parse_word(&data->cmd, &temp);
		else if (temp->type == REDIRECT_IN)
			set_infile(&data->cmd, &temp);
		else if (temp->type == REDIRECT_OUT)
			set_outfile(&temp, &data->cmd);
		else if (temp->type == HEREDOC)
			parse_heredoc(data, &data->cmd, &temp);
		else if (temp->type == APPEND)
			parse_append(&data->cmd, &temp);
		else if (temp->type == PIPE)
			parse_pipe(&data->cmd, &temp);
		else if (temp->type == END)
			break ;
	}
	prep_no_arg_commands(data);
}
