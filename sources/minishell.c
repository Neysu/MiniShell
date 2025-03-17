/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/17 20:45:00 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	t_envp	*env_data;
	t_cmd	*cmd_data;

	(void)argc;
	(void)argv;
	env_data = get_env(envp);
	while (1)
	{
		line = readline("MINISHELL > ");
		cmd_data = parse_cmd(line);
		if (is_builtin(line))
			exec_buitlins(line, env_data);
		else
			exec_cmd(cmd_data, env_data);
	}
	return (0);
}
