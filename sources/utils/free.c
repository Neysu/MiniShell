/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:51 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/19 15:27:42 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	free_str_tab(char **tab)
{
	int	i;

	i = 0;
	if (tab)
	{
		while (tab[i])
		{
			if (tab[i])
			{
				free_ptr(tab[i]);
				tab[i] = NULL;
			}
			i++;
		}
		free(tab);
		tab = NULL;
	}
}

void	lst_delone_token(t_token *lst, void (*del)(void *))
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

void	lst_delone_cmd(t_cmd *lst, void (*del)(void *))
{
	if (lst->cmd)
		free_str_tab(lst->cmd);
	if (lst->infile)
		(*del)(lst->infile);
	if (lst->outfile)
		(*del)(lst->outfile);
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

void	free_ptr(void *ptr)
{
	if (ptr != NULL)
	{
		free(ptr);
		ptr = NULL;
	}
}

void	free_data(t_data *data, bool clear_history)
{
	if (data && data->user_input)
	{
		free_ptr(data->user_input);
		data->user_input = NULL;
	}
	if (data && data->token)
		lst_clear_token(&data->token, &free_ptr);
	if (data && data->cmd)
		lst_clear_cmd(&data->cmd, &free_ptr);
	if (clear_history == true)
	{
		rl_clear_history();
	}
}

void	exit_shell(t_data *data, int exit_code)
{
	if (data)
		free_data(data, true);
	exit(exit_code);
}

void	print_exit_shell(t_data *data, int exit_code)
{
	write(STDERR_FILENO, "exit\n", 5);
	free_tokens(data->token);
	exit_shell(data, exit_code);
}

void	free_tokens(t_token *head)
{
	t_token *tmp;

	while (head)
	{
		tmp = head->next;
		if (head->str)
			free(head->str);
		free(head);
		head = tmp;
	}
}
