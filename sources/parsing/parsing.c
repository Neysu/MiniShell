/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/21 16:26:30 by rureshet         ###   ########.fr       */
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

t_cmd	*parsing(char *line)
{
	t_cmd	*cmd_data;
	char	**user_input;
	t_cmd	*head;
	t_cmd	*current;
	t_data	*data;

	user_input = ft_split(line, ';');
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
	if (token_generator(data, data->user_input) == EXIT_FAILURE)
		return (false);
	return (true);
}




