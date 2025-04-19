/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/04/19 15:21:00 by rureshet         ###   ########.fr       */
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

int	ft_isspace(int c)
{
	if (c == ' ' || c == '\t' || c == '\n' || c == '\r'
		|| c == '\v' || c == '\f')
		return (c);
	return (0);
}

static bool	input_is_space(char *input)
{
	int	i;

	i = 0;
	while (input[i])
	{
		if (!ft_isspace(input[i]))
			return (false);
		i++;
	}
	return (true);
}

void	parsing(t_data *data)
{
	char	**user_input;
	int		i;

	if (data->user_input == NULL)
		print_exit_shell(data, data->exit_code);
	user_input = ft_split(data->user_input, ';');
	if (!user_input)
		exit_shell(data, EXIT_FAILURE);
	i = 0;
	while (user_input[i])
	{
		data->user_input = ft_strdup(user_input[i]);
		if (parser_user_input(data) == true)
		{
			//show_lists(data);
			data->exit_code = 0;
			if (data->cmd && is_builtin(data->cmd))
				exec_buitlins(data->user_input, data);
			else
				exec(data);
		}
		else
			data->exit_code = 1;
		i++;
		free_data(data, false);
	}
	free_str_tab(user_input);
}

bool	parser_user_input(t_data *data)
{

	if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	else if (input_is_space(data->user_input))
		return (true);
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
