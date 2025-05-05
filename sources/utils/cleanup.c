/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cleanup.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:19:31 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/05 14:20:22 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	lst_delone_token(t_token *lst, void (*del)(void *))
{
	if (del && lst && lst->str)
	{
		(*del)(lst->str);
		lst->str = NULL;
	}
	if (del && lst && lst->str_backup)
	{
		(*del)(lst->str_backup);
		lst->str_backup = NULL;
	}
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	free_ptr(lst);
}

void	lst_clear_token(t_token **lst, void (*del)(void *))
{
	t_token	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		lst_delone_token(*lst, del);
		*lst = tmp;
	}
}

static void	cleanup_cmd_node(t_cmd *lst, void (*del)(void *))
{
	if (lst->cmd)
		free_str_tab(lst->cmd);
	if (del)
	{
		if (lst->path)
			(*del)(lst->path);
		if (lst->infile)
			(*del)(lst->infile);
		if (lst->outfile)
			(*del)(lst->outfile);
		if (lst->heredoc_delimiter)
			(*del)(lst->heredoc_delimiter);
	}
	if (lst->pipefd)
		free(lst->pipefd);
	if (lst->fd > 2)
		close(lst->fd);
	if (lst->fd_in > 2)
		close(lst->fd_in);
	if (lst->fd_out > 2)
		close(lst->fd_out);
	if (lst->stdin_backup > 2)
		close(lst->stdin_backup);
	if (lst->stdout_backup > 2)
		close(lst->stdout_backup);
}

void	lst_delone_cmd(t_cmd *lst, void (*del)(void *))
{
	cleanup_cmd_node(lst, del);
	if (lst->prev)
		lst->prev->next = lst->next;
	if (lst->next)
		lst->next->prev = lst->prev;
	lst->cmd = NULL;
	lst->path = NULL;
	lst->pipefd = NULL;
	lst->infile = NULL;
	lst->outfile = NULL;
	lst->heredoc_delimiter = NULL;
	lst->next = NULL;
	lst->prev = NULL;
	(*del)(lst);
}

void	lst_clear_cmd(t_cmd **lst, void (*del)(void *))
{
	t_cmd	*temp;

	temp = NULL;
	while (*lst != NULL)
	{
		temp = (*lst)->next;
		lst_delone_cmd(*lst, del);
		*lst = temp;
	}
}
