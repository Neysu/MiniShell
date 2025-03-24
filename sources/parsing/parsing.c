/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/03/24 19:14:39 by rureshet         ###   ########.fr       */
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

// t_cmd	*create_cmd(int type, char *cmd)
// {
// 	t_cmd *cmd_data;

// 	cmd_data = ft_calloc(sizeof(t_cmd), 1);
// 	if (!cmd_data)
// 		return (NULL);
// 	//cmd_data->type = type;
// 	cmd_data->cmd = ft_split(cmd, ' ');
// 	cmd_data->next = NULL;
// 	return (cmd_data);
// }

void	parsing(char *line, t_data *data)
{
	char	**user_input;

	signal(SIGINT, &sig_int);
	signal(SIGQUIT, &sig_quit);
	user_input = ft_split(line, ';');
	if (!user_input)
		return ;
	if (!data)
		return ;
	int i = 0;
	while (user_input[i])
	{
		data->user_input = ft_strdup(user_input[i]);
		if (parser_user_input(data) == true)
			show_lists(data);
		i++;
	}
}

bool	parser_user_input(t_data *data)
{
	if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	add_history(data->user_input);
	if (token_generator(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	if (envp_check(&data->token) == FAILURE)
		return (false);
	return (true);
}




