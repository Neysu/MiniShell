/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/18 18:51:48 by rureshet         ###   ########.fr       */
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
		if (data->user_input == NULL)
			exit_shell(&data, EXIT_SUCCESS, true);
		parsing(&data);
		if (data->cmd && is_builtin(data->cmd))
			exec_buitlins(data->user_input, &data);
		else
			exec(&data);
		lst_clear_cmd(&data->cmd, &free_ptr);
		lst_clear_token(&data->token, &free_ptr);
		free(data->user_input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(argc) || !init_data(&data, envp))
		exit_shell(NULL, EXIT_FAILURE, false);
	minishell(&data);
	exit_shell(&data, EXIT_SUCCESS, false);
	return (0);
}
