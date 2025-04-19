/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/19 15:15:17 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sig g_sig;

static bool	start_check(int argc)
{
	if (argc != 1)
	{
		ft_putendl_fd("Usage: ./minishell\n", 2);
		return(false);
	}
	return (true);
}

bool	init_data(t_data *data, char **envp)
{
	data->envp = get_env(envp);
	if (!data->envp)
	{
		error_message("Could not initialize environment", NULL, false);
		return (false);
	}
	data->user_input = NULL;
	data->work = true;
	data->token = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	return (true);
}

void	minishell(t_data *data)
{
	while (data->work)
	{
		set_signal_interactive();
		data->user_input = readline(PROMPT);
		set_signal_noninteractive();
		parsing(data);
		free(data->user_input);
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
	exit_shell(&data, EXIT_SUCCESS);
	return (0);
}
