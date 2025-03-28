/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/27 17:26:31 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sig g_sig;

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
	return (true);
}

int	main(int argc, char **argv, char **envp)
{
	// t_envp	*env_data;
	// t_cmd	*cmd_data = NULL;
	t_data	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, envp))
		error_message("Could not initialize data", NULL, false);
	while (1)
	{
		set_signal_interactive();
		data.user_input = readline(PROMPT);
		set_signal_noninteractive();
		parsing(&data);
		// if (is_builtin(line))
		// 	exec_buitlins(line, data->envp);
		// else
		// 	exec_cmd(cmd_data, data->envp);
	}
	return (0);
}
