/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   free.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 12:59:51 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/28 12:43:18 by rureshet         ###   ########.fr       */
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

void	free_void_tab(char **tab)
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

void	lst_delone_envp(t_envp *lst, void (*del)(void *))
{
	if (del && lst && lst->var)
	{
		(*del)(lst->var);
		lst->var = NULL;
	}
	if (lst->next)
		lst->next = NULL;
	free_ptr(lst);
}

void	lst_clear_envp(t_envp **lst, void (*del)(void *))
{
	t_envp	*tmp;

	tmp = NULL;
	while (*lst != NULL)
	{
		tmp = (*lst)->next;
		lst_delone_envp(*lst, del);
		*lst = tmp;
	}
}

void	lst_delone_cmd(t_cmd *lst, void (*del)(void *))
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
	if (data && data->envp)
		lst_clear_envp(&data->envp, &free_ptr);
	if (clear_history == true)
	{
		if (data && data->working_dir)
			free_ptr(data->working_dir);
		if (data && data->old_working_dir)
			free_ptr(data->old_working_dir);
		if (data && data->env_list)
			free_str_tab(data->env_list);
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
	// lst_clear_token(&data->token, &free_ptr);
	//free_tokens(data->token);
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
		if (head->str_backup)
			free(head->str_backup);
		free(head);
		head = tmp;
	}
}

void	free_env_array(char **env_array)
{
	int	i;

	if (!env_array)
		return;
	i = 0;
	while (env_array[i])
	{
		free(env_array[i]);
		i++;
	}
	free(env_array);
}
