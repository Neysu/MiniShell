/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/19 15:42:00 by rureshet         ###   ########.fr       */
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

t_cmd	*create_cmd(int type, char *cmd)
{
	t_cmd *cmd_data;

	cmd_data = ft_calloc(sizeof(t_cmd), 1);
	if (!cmd_data)
		return (NULL);
	//cmd_data->type = type;
	cmd_data->cmd = ft_split(cmd, ' ');
	cmd_data->next = NULL;
	return (cmd_data);
}

int	is_separator(char *str, int i)
{
	if ((str[i] >= 9 && str[i] <= 13) || str[i] == 32)
		return (SPACES);
	else if (str[i] == '|')
			return (PIPE);
	else if (str[i] == '>')
			return (REDIRECT_IN);
	else if (str[i] == '<')
			return (REDIRECT_OUT);
	else if (str[i] == '>' && str[i + 1] == '>')
			return (APPEND);
	else if (str[i] == '<' && str[i + 1] == '<')
			return (HEREDOC);
	else if (str[i] == '\0')
			return (END);
	return (0);
}

t_cmd	*parsing(char *line)
{
	t_cmd	*cmd_data;
	char	**user_input;
	t_cmd	*head;
	t_cmd	*current;
	t_data	*data;

	user_input = ft_split(line, '&');
	head = NULL;
	current = NULL;
	int i = 0;
	while (user_input[i])
	{
		data->user_input = user_input[i];
		if (parser_user_input(&data) == true)
			;// execute;
		int type = WORD;
		if (user_input[i][0] == '$')
			type = ENV;
		else if (ft_strcmp(user_input[i], "|") == 0)
			type = PIPE;
		else if (ft_strcmp(user_input[i], "<") == 0)
			type = REDIRECT_IN;
		else if (ft_strcmp(user_input[i], ">") == 0)
			type = REDIRECT_OUT;
		else if (ft_strcmp(user_input[i], "<<") == 0)
			type = APPEND;
		else if (ft_strcmp(user_input[i], ">>") == 0)
			type = HEREDOC;
		cmd_data = create_cmd(type, user_input[i]);

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

bool	parser_user_input(t_data *data)
{
	if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	add_history(data->user_input);
	tokenizator(data, data->user_input);
	return (true);
}

void	tokenizator(t_data *data, char *str)
{
	// Create tokens
}
