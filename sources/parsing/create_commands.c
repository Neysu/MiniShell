/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:44:03 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/19 15:13:37 by rureshet         ###   ########.fr       */
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

void	set_cmd_type(t_data *data, t_token **token, int type)
{
	t_cmd *last_cmd;

	last_cmd = lst_last_cmd(data->cmd);
	last_cmd->type = type;
	*token = (*token)->next;
	lst_addback_cmd(&data->cmd, lst_new_cmd());
}

void	set_outfile(t_token **token, t_data *data, int type)
{
	t_cmd *last;

	last = lst_last_cmd(data->cmd);
	if (type == REDIRECT_OUT && (*token)->next->type == WORD)
		last->outfile = ft_strdup((*token)->next->str);
	else if (type == APPEND && (*token)->next->type == WORD)
		last->outfile = ft_strdup((*token)->next->str);
	*token = (*token)->next;
	set_cmd_type(data, token, type);
}

void	set_infile(t_token **token, t_data *data)
{
	t_cmd *last;

	last = lst_last_cmd(data->cmd);
	if ((*token)->type == REDIRECT_IN && (*token)->next->type == WORD)
	{
		last->infile = ft_strdup((*token)->next->str);
		*token = (*token)->next;
	}
	set_cmd_type(data, token, REDIRECT_IN);
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
			set_cmd_type(data, &temp, REDIRECT_IN);
		else if (temp->type == REDIRECT_OUT)
			set_cmd_type(data, &temp, REDIRECT_OUT);
		else if (temp->type == PIPE)
			set_cmd_type(data, &temp, PIPE);
		else if (temp->type == APPEND)
			set_cmd_type(data, &temp, APPEND);
		else if (temp->type == HEREDOC)
			set_cmd_type(data, &temp, HEREDOC);
		else if (temp->type == END)
			break ;
	}
}

