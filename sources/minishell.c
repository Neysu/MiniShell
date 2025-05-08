/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/08 15:31:39 by rureshet         ###   ########.fr       */
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

static void	minishell(t_data *data)
{
	while (1)
	{
		set_signal_interactive();
		data->user_input = readline(PROMPT);
		set_signal_noninteractive();
		if (data->user_input == NULL)
			print_exit_shell(data, data->exit_code);
		if (parser_user_input(data) == true)
			data->exit_code = execute(data);
		else
			data->exit_code = 1;
		free_data(data, false);
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
