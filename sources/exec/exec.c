/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:29 by elliot            #+#    #+#             */
/*   Updated: 2025/03/28 18:43:03 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/types.h>
#include <sys/wait.h>

char	**env_to_str(t_envp *envp)
{
	char	**env;
	t_envp	*current;
	int		i;

	i = 0;
	env = ft_calloc(sizeof(char *), ft_envsize(envp));
	current = envp;
	while (current->next)
	{
		env[i] = ft_strdup(current->var);
		i++;
		current = current->next;
	}
	return (env);
}

int	exec_cmd(t_cmd *cmd_data, t_envp *envp_data)
{
	char	*path;
	char	**envp;
	int		status;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		_exit(1);
	if (pid == 0)
	{
		path = findcmd(cmd_data, envp_data);
		if (!path)
			exit (1);
		envp = env_to_str(envp_data);
		if (execve(path, &cmd_data->cmd, envp) == -1)
			(ft_printf(ERRORCMD, cmd_data->cmd[0]), ft_free_arr(&cmd_data->cmd), ft_free_arr(envp), exit(1));
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
