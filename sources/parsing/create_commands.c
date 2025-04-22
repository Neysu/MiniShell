/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:44:03 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/22 21:55:50 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	fill_cmd(t_token **token_node, t_cmd *last_cmd, char *str)
{
	t_token *temp = *token_node;

	if (!last_cmd->cmd) {
		last_cmd->cmd = malloc(sizeof(char *) * 2);
		if (!last_cmd->cmd) return (FAILURE);
		last_cmd->cmd[0] = ft_strdup(str);
		if (!last_cmd->cmd[0]) {
			free(last_cmd->cmd);
			return (FAILURE);
		}
		last_cmd->cmd[1] = NULL;
	}
	else if (last_cmd->cmd[0] == NULL) {
		last_cmd->cmd[0] = ft_strdup(str);
		if (!last_cmd->cmd[0]) {
			return (FAILURE);
		}
	}
	if (token_node)
		*token_node = temp;
	return (SUCCESS);
}

void	split_var_cmd_token(t_cmd *last_cmd, char *cmd_str)
{
	t_token		*new_tokens;
	t_token		*tmp;
	char		**strs;
	int			i;

	new_tokens = NULL;
	strs = ft_split(cmd_str, ' ');
	if (!strs)
		return ;
	fill_cmd(NULL, last_cmd, strs[0]);
	if (strs[1])
		new_tokens = lst_new_token(ft_strdup(strs[1]), WORD, DEFAULT);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		lst_addback_token(&new_tokens,
			lst_new_token(ft_strdup(strs[i]), WORD, DEFAULT));
	lst_addback_token(&new_tokens,
		lst_new_token(NULL, END, DEFAULT));
	fill_args(&new_tokens, last_cmd);
	lstclear_token(&tmp, &free_ptr);
	free_str_tab(strs);
}

void	parse_word(t_cmd **cmd, t_token **token)
{
	t_token		*temp;
	t_cmd	*last_cmd;

	temp = *token;
	while (temp->type == WORD || temp->type == ENV)
	{
		last_cmd = lst_last_cmd(*cmd);
		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
			|| last_cmd->cmd == NULL || last_cmd->cmd[0] == NULL)
		{
			if (temp->type == ENV && contains_space(temp->str))
				split_var_cmd_token(last_cmd, temp->str);
			else
				fill_cmd(&temp, last_cmd, temp->str);
			temp = temp->next;
		}
		else
			fill_args(&temp, last_cmd);
	}
	*token = temp;
}

static void	prep_no_arg_commands(t_data *data)
{
	t_cmd	*cmd;

	if (!data || !data->cmd)
		return ;
	cmd = data->cmd;
	while (cmd && cmd->cmd[0])
	{
		if (!cmd->cmd)
		{
			cmd->cmd = malloc(sizeof * cmd->cmd * 2);
			cmd->cmd[0] = ft_strdup(cmd->cmd[0]);
			cmd->cmd[1] = NULL;
		}
		cmd = cmd->next;
	}
	cmd = lst_last_cmd(data->cmd);
}

void	set_cmd_type(t_data *data, t_token **token, int type)
{
	t_cmd *last_cmd;

	last_cmd = lst_last_cmd(data->cmd);
	last_cmd->type = type;
	*token = (*token)->next;
	lst_addback_cmd(&data->cmd, lst_new_cmd());
}

bool	remove_old_file_ref(t_cmd *cmd, bool infile)
{
	if (infile == true && cmd->infile)
	{
		if (cmd->fd_in == -1 || (cmd->outfile && cmd->fd_out == -1))
			return (false);
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

void	open_infile(t_cmd *cmd, char *file)
{
	if (!remove_old_file_ref(cmd, true))
		return ;
	cmd->infile = ft_strdup(file);
	if (cmd->infile && cmd->infile[0] == '\0')
	{
		error_message(cmd->infile,"ambiguous redirect", false);
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
		error_message(cmd->infile,"ambiguous redirect", false);
		return ;
	}
	cmd->fd_out = open(cmd->outfile, O_WRONLY | O_CREAT | O_TRUNC, 0664);
	if (cmd->fd_out == -1)
		printf("File dont opened: %d\n", cmd->fd_in);
}

void	set_outfile(t_token **token, t_cmd **last_cmd)
{
	t_token		*temp;
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

void	create_commands(t_data *data, t_token *token)
{
	t_token *temp;

	temp = token;
	if ( temp->type == END)
		return ;
	while (temp->next != NULL)
	{
		if (temp == token)
			lst_addback_cmd(&data->cmd, lst_new_cmd());
		if (temp->type == WORD || temp->type == ENV)
			parse_word(&data->cmd, &temp);
		else if (temp->type == REDIRECT_IN)
		{
			set_infile(&temp, &data->cmd);
			//set_cmd_type(data, &temp, REDIRECT_IN);
		}
		else if (temp->type == REDIRECT_OUT)
			set_outfile(&temp, &data->cmd);
		else if (temp->type == PIPE)
			set_cmd_type(data, &temp, PIPE);
		else if (temp->type == APPEND)
			set_cmd_type(data, &temp, APPEND);
		else if (temp->type == HEREDOC)
			set_cmd_type(data, &temp, HEREDOC);
		else if (temp->type == END)
			break ;
	}
	prep_no_arg_commands(data);
}

