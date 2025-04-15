/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:29 by elliot            #+#    #+#             */
/*   Updated: 2025/04/08 00:14:20 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	exec_single(t_data *data)
{
	pid_t	pid;
	int		status;

	pid = fork();
	if (pid == 0)
	{
		if (is_builtin(data->cmd))
		 	exec_buitlins(data->user_input, data);
		else
			exec_cmd(data->cmd, data->envp);
	}
	waitpid(pid, &status, 0);
}

int		exec(t_data *data)
{
	t_cmd *current = data->cmd;

	if (current)
	{
		if (current->type == REDIRECT_OUT || current->type == REDIRECT_IN
			|| current->type == APPEND)
			redirect(current, data);
		if (current->type == COMMAND)
			exec_single(data);
		current = current->next;
	}
	return (1);
}

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

	path = findcmd(cmd_data, envp_data);
	if (!path)
		return (ft_puterror(cmd_data->cmd[0]), 1);
	envp = env_to_str(envp_data);
	execve(path, cmd_data->cmd, envp);
	perror("execve");
	ft_free_arr(cmd_data->cmd);
	ft_free_arr(envp); 
	exit(127);
}
