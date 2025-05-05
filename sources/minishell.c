/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/05 14:46:00 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

static bool	start_check(int argc)
{
	if (argc != 1)
	{
		ft_putendl_fd("Usage: ./minishell\n", 2);
		return (false);
	}
	return (true);
}

static int	process_user_input(t_data *data, char *input_line)
{
	char	**commands;
	int		i;
	int		exit_code;

	commands = ft_split(input_line, ';');
	if (!commands)
		exit_shell(data, EXIT_FAILURE);
	i = 0;
	while (commands[i])
	{
		data->user_input = ft_strdup(commands[i]);
		if (parser_user_input(data) == true)
		{
			show_lists(data);
			exit_code = execute(data);
		}
		else
			exit_code = 1;
		i++;
		free_data(data, false);
	}
	free_str_tab(commands);
	return (exit_code);
}

void	minishell(t_data *data)
{
	while (1)
	{
		set_signal_interactive();
		data->user_input = readline(PROMPT);
		set_signal_noninteractive();
		if (data->user_input == NULL)
			print_exit_shell(data, data->exit_code);
		data->exit_code = process_user_input(data, data->user_input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(argc) || !init_data(&data, envp))
		exit_shell(NULL, EXIT_FAILURE);
	minishell(&data);
	exit_shell(&data, data.exit_code);
	return (0);
}
