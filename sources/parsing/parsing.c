/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/18 14:37:09 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(char *line)
{
	if (!ft_strncmp(line, "echo", 4))
		return (1);
	if (!ft_strncmp(line, "cd", 2))
		return (1);
	if (!ft_strncmp(line, "pwd", 3))
		return (1);
	if (!ft_strncmp(line, "export", 6))
		return (1);
	if (!ft_strncmp(line, "unset", 5))
		return (1);
	if (!ft_strncmp(line, "env", 3))
		return (1);
	if (!ft_strncmp(line, "exit", 4))
		return (1);
	return (0);
}

t_cmd	*create_cmd(t_token_type type, char *cmd)
{
	t_cmd *cmd_data;

	cmd_data = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd_data)
		return (NULL);
	cmd_data->type = type;
	cmd_data->cmd = ft_strdup(cmd);
	cmd_data->next = NULL;
	return (cmd_data);
}

t_cmd	*parse_cmd(char *line)
{
	t_cmd	*cmd_data;
	char	**cmd;
	t_cmd	*head;
	t_cmd	*current;

	cmd = ft_split(line, ' ');
	head = NULL;
	current = NULL;
	int i = 0;
	while (cmd[i])
	{
		t_token_type type = TOKEN_WORD;

		if (ft_strcmp(cmd[i], "|") == 0)
			type = TOKEN_PIPE;
		else if (ft_strcmp(cmd[i], "<") == 0)
			type = TOKEN_REDIRECT_IN;
		else if (ft_strcmp(cmd[i], ">") == 0)
			type = TOKEN_REDIRECT_OUT;
		else if (ft_strcmp(cmd[i], "<<") == 0)
			type = TOKEN_APPEND;
		else if (ft_strcmp(cmd[i], ">>") == 0)
			type = TOKEN_HEREDOC;
		cmd_data = create_cmd(type, cmd[i]);

		if (!head)
		{
			head = cmd_data;
			current = head;
		}
		else
		{
			current->next = cmd_data;
			current = current->next;
		}
		i++;
	}
	return (head);
}
