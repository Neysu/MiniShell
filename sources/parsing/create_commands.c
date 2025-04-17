/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   create_commands.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 16:44:03 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/17 17:07:49 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

t_cmd	*lst_new_cmd(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	new_node->cmd = NULL;
	new_node->type = 10;
	new_node->fd = -1;
	new_node->infile = NULL;
	new_node->outfile = NULL;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

t_cmd	*lst_add_new_cmd(void)
{
	t_cmd	*new_node;

	new_node = (t_cmd *)malloc(sizeof(t_cmd));
	if (!new_node)
		return (NULL);
	ft_memset(new_node, 0 , sizeof(t_cmd));
	new_node->cmd = NULL;
	new_node->fd = -1;
	new_node->next = NULL;
	new_node->prev = NULL;
	return (new_node);
}

void	lst_addback_cmd(t_cmd **cmd_list, t_cmd *new_node)
{
	t_cmd *start;

	start = *cmd_list;
	if(start == NULL)
	{
		*cmd_list = new_node;
		return ;
	}
	if (cmd_list && *cmd_list && new_node)
	{
		while (start->next != NULL)
			start = start->next;
		start->next = new_node;
		new_node->prev = start;
	}
}

t_cmd	*lst_last_cmd(t_cmd *cmd)
{
	while (cmd->next != NULL)
		cmd = cmd->next;
	return (cmd);
}

int	args_count(t_token *token)
{
	int	i;

	i = 0;
	while(token && (token->type == WORD || token->type == ENV))
	{
		token = token->next;
		i++;
	}
	return(i);
}

int	create_args_default_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		nb_args;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	nb_args = 1;
	while (temp->type == WORD || temp->type == ENV)
	{
		nb_args++;
		temp = temp->next;
	}
	temp = *token_node;
	last_cmd->cmd = malloc(sizeof(char *) * (nb_args + 1));
	if (!last_cmd->cmd)
		return (FAILURE);
	i = 1;
	while (temp->type == WORD || temp->type == ENV)
	{
		last_cmd->cmd[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	last_cmd->cmd[i] = NULL;
	*token_node = temp;
	return (SUCCESS);
}

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

static char	**copy_default_in_new_tab(
	int len, char **new_tab, t_cmd *last_cmd, t_token **tk_node)
{
	int		i;
	t_token	*temp;

	i = 0;
	temp = *tk_node;
	while (i < len)
	{
		new_tab[i] = last_cmd->cmd[i];
		i++;
	}
	while (temp->type == WORD || temp->type == ENV)
	{
		new_tab[i] = ft_strdup(temp->str);
		i++;
		temp = temp->next;
	}
	new_tab[i] = NULL;
	return (new_tab);
}

int	add_args_default_mode(t_token **token_node, t_cmd *last_cmd)
{
	int		i;
	int		len;
	char	**new_tab;
	t_token	*temp;

	i = 0;
	temp = *token_node;
	while (temp->type == WORD || temp->type == ENV)
	{
		i++;
		temp = temp->next;
	}
	len = 0;
	while (last_cmd->cmd[len])
		len++;
	new_tab = malloc(sizeof(char *) * (i + len + 1));
	if (!new_tab)
		return (FAILURE);
	new_tab = copy_default_in_new_tab(len, new_tab, last_cmd, token_node);
	free(last_cmd->cmd);
	last_cmd->cmd = new_tab;
	*token_node = temp;
	return (SUCCESS);
}

int	fill_args(t_token **token_node, t_cmd *last_cmd)
{
	if (last_cmd && !(last_cmd->cmd))
		return (create_args_default_mode(token_node, last_cmd));
	else
		return (add_args_default_mode(token_node, last_cmd));
	return (SUCCESS);
}

bool	contains_space(char *str)
{
	int	i;

	i = 0;
	while (str[i])
	{
		if (str[i] == ' ')
			return (true);
		i++;
	}
	return (false);
}

void	lstdelone_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->str)
	{
		(*del)(lst->str);
		lst->str = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free_ptr(lst);
}

void	lstclear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		lstdelone_token(*lst, del);
		*lst = tmp;
	}
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
			{
				fill_cmd(&temp, last_cmd, temp->str);
			}
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
		if (temp->type == PIPE)
			set_cmd_type(data, &temp, PIPE);
		if (temp->type == REDIRECT_IN)
			set_infile(&temp, data);
		if (temp->type == REDIRECT_OUT)
			set_outfile(&temp, data, temp->type);
		if (temp->type == APPEND)
			set_outfile(&temp, data, temp->type);
		if (temp->type == HEREDOC)
			set_cmd_type(data, &temp, HEREDOC);
		if (temp->type == END && data->cmd->type == DEFAULT)
			return (set_cmd_type(data, &temp, COMMAND));
	}
}

