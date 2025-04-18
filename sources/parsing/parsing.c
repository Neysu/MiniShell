/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/04/07 17:42:46 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	is_builtin(t_cmd *cmd_data)
{
	if (!cmd_data || !cmd_data->cmd || !cmd_data->cmd[0])
		return (0);
	if (!ft_strncmp(cmd_data->cmd[0], "echo", -1))
		return (ft_putendl_fd("echo is on", STDERR), 1);
	if (!ft_strncmp(cmd_data->cmd[0], "cd", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "pwd", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "export", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "unset", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "env", -1))
		return (1);
	if (!ft_strncmp(cmd_data->cmd[0], "exit", -1))
		return (1);
	return (0);
}

void	parsing(t_data *data)
{
	char	**user_input;

	user_input = ft_split(data->user_input, ';');
	if (!user_input)
		return ;
	int i = 0;
	while (user_input[i])
	{
		data->user_input = ft_strdup(user_input[i]);
		if (parser_user_input(data) == true)
			data->exit_code = 0;
		else
			data->exit_code = 1;
		i++;
	}
	ft_free_arr(user_input);
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
	expand_variables(data, &data->token);
	quotes_handler(data);
	create_commands(data, data->token);
	return (true);
}
