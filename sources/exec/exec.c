/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:29 by elliot            #+#    #+#             */
/*   Updated: 2025/03/09 03:27:47 by elliot           ###   ########.fr       */
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

int	exec_cmd(t_cmd *cmd_data, t_envp *envp_data, char **test)
{
	char	*path;
	char	**envp;
	int		status;
	(void)test;
	pid_t	pid;

	pid = fork();
	if (pid == -1)
		return (1);
	if (pid == 0)
	{
		path = findcmd(cmd_data, envp_data);
		if (!path)
			return (1);
		envp = env_to_str(envp_data);
		if (execve(path, cmd_data->cmd, envp) == -1)
		{
			ft_puttab_fd(cmd_data->cmd, 1);
			ft_putchar_fd('\n', 1);
			ft_putstr_fd("minishell: ", 2);
			ft_putstr_fd(cmd_data->cmd[0], 2);
			ft_putstr_fd(": command not found\n", 2);
			exit(127);
		}
		free(path);
		exit(1);
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}