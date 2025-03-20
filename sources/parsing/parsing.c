/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/20 17:00:36 by rureshet         ###   ########.fr       */
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
		i++;
	}
}

bool	parser_user_input(t_data *data)
{
	if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	add_history(data->user_input);
	token_generator(data, data->user_input);
	return (true);
}

int	check_quotes(int status, char *str, int i)
{
	if (str[i] == '\'' && status == DEFAULT)
		status = SQUOTE;
	if (str[i] == '\"' && status == DEFAULT)
		status = DQUOTE;
	if (str[i] == '\'' && status == SQUOTE)
		status = DEFAULT;
	if (str[i] == '\"' && status == DQUOTE)
		status = DEFAULT;
	return (status);
}

void	token_generator(t_data *data, char *str)
{
	int	str_len;
	int	i;
	int	type;
	int	status;

	str_len = ft_strlen(str);
	i = 0;
	status = DEFAULT;
	while (i < str_len)
	{
		status = check_quotes(status, str, i);
		if (status == DEFAULT)
		{
			type = is_separator(str, i);
			if (type)
			{
				if (i != 0 && is_separator(str, i - 1) == 0)
					// function for words
				if (type == PIPE || type == REDIRECT_IN ||type == REDIRECT_OUT || type == APPEND || type == HEREDOC || type == END)
					// function for separators
					if (type == APPEND || type == HEREDOC)
						i++;
			}
		}
		i++;
	}
	if (status != DEFAULT)
	{
		error_message("Unclosed quotation mark detected");
	}
}
