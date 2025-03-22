/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/22 18:46:35 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

bool	init_data(t_data *data, char **envp)
{
	data->envp = get_env(envp);
	if (!data->envp)
	{
		error_message("Could not initialize environment");
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
	char	*line;
	// t_envp	*env_data;
	// t_cmd	*cmd_data = NULL;
	t_data	data;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, envp))
		error_message("Could not initialize data");
	while (1)
	{
		line = readline("MINISHELL > ");
		parsing(line, &data);
		// if (is_builtin(line))
		// 	exec_buitlins(line, data->envp);
		// else
		// 	exec_cmd(cmd_data, data->envp);
	}
	return (0);
}
