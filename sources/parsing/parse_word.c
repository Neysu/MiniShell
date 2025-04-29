/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_word.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 18:45:35 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/29 13:02:24 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static int	fill_cmd(t_token **token_node, t_cmd *last_cmd, char *str)
{
	t_token	*temp;

	temp = *token_node;
	if (!last_cmd->cmd)
	{
		last_cmd->cmd = malloc(sizeof(char *) * 2);
		if (!last_cmd->cmd)
			return (FAILURE);
		last_cmd->cmd[0] = ft_strdup(str);
		if (!last_cmd->cmd[0])
		{
			free(last_cmd->cmd);
			return (FAILURE);
		}
		last_cmd->cmd[1] = NULL;
	}
	else if (last_cmd->cmd[0] == NULL)
	{
		last_cmd->cmd[0] = ft_strdup(str);
		if (!last_cmd->cmd[0])
			return (FAILURE);
	}
	if (token_node)
		*token_node = temp;
	return (SUCCESS);
}

static void	split_var_cmd_token(t_cmd *last_cmd, char *cmd_str)
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
		new_tokens = lst_new_token(ft_strdup(strs[1]), NULL, WORD, DEFAULT);
	tmp = new_tokens;
	i = 1;
	while (strs[++i])
		lst_addback_token(&new_tokens,
			lst_new_token(ft_strdup(strs[i]), NULL, WORD, DEFAULT));
	lst_addback_token(&new_tokens,
		lst_new_token(NULL, NULL, END, DEFAULT));
	fill_args(&new_tokens, last_cmd);
	lstclear_token(&tmp, &free_ptr);
	free_str_tab(strs);
}

static void	process_word_token(t_token **temp, t_cmd *last_cmd)
{
	if ((*temp)->prev == NULL || ((*temp)->prev && (*temp)->prev->type == PIPE)
		|| last_cmd->cmd[0] == NULL)
	{
		if ((*temp)->type == ENV && contains_space((*temp)->str))
			split_var_cmd_token(last_cmd, (*temp)->str);
		else if ((*temp)->str)
			last_cmd->cmd[0] = ft_strdup((*temp)->str);
		*temp = (*temp)->next;
	}
	else
		fill_args(temp, last_cmd);
}

void	parse_word(t_cmd **cmd, t_token **token)
{
	t_token	*temp;
	t_cmd	*last_cmd;

	temp = *token;
	while (temp && (temp->type == WORD || temp->type == ENV))
	{
		last_cmd = lst_last_cmd(*cmd);
		if (!last_cmd->cmd)
		{
			last_cmd->cmd = malloc(sizeof(char *) * 2);
			if (!last_cmd->cmd)
				return ;
			last_cmd->cmd[0] = NULL;
			last_cmd->cmd[1] = NULL;
		}
		process_word_token(&temp, last_cmd);
	}
	*token = temp;
}

// void	parse_word(t_cmd **cmd, t_token **token)
// {
// 	t_token	*temp;
// 	t_cmd	*last_cmd;

// 	temp = *token;
// 	while (temp->type == WORD || temp->type == ENV)
// 	{
// 		last_cmd = lst_last_cmd(*cmd);
// 		if (!last_cmd->cmd)
// 		{
// 			last_cmd->cmd = malloc(sizeof(char *) * 2);
// 			if (!last_cmd->cmd)
// 				return ;
// 			last_cmd->cmd[0] = NULL;
// 			last_cmd->cmd[1] = NULL;
// 		}
// 		if (temp->prev == NULL || (temp->prev && temp->prev->type == PIPE)
// 			|| last_cmd->cmd[0] == NULL)
// 		{
// 			if (temp->type == ENV && contains_space(temp->str))
// 				split_var_cmd_token(last_cmd, temp->str);
// 			else if (temp->str)
// 				last_cmd->cmd[0] = ft_strdup(temp->str);
// 			temp = temp->next;
// 		}
// 		else
// 			fill_args(&temp, last_cmd);
// 	}
// 	*token = temp;
// }
