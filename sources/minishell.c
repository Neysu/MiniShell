/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/09 03:29:55 by elliot           ###   ########.fr       */
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
	while (1)
	{
		env_data = get_env(envp);
		line = readline("MINISHELL > ");
		cmd_data = parse_cmd(line);
		exec_cmd(cmd_data, env_data, envp);
	}
	return (0);
}
