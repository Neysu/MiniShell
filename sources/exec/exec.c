/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:29 by elliot            #+#    #+#             */
/*   Updated: 2025/04/07 16:36:29 by elliot           ###   ########.fr       */
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
		exec_cmd(data->cmd, data->envp);
	}
	waitpid(pid, &status, 0);
}

int		exec(t_data *data)
{
	t_cmd *current = data->cmd;

	while (current)
	{
		if (current->type == REDIRECT_OUT)
			redirect_out(current, data);
		if (current->type == REDIRECT_IN)
			redirect_inf(current, data);
		if (!current->type)
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
		return (perror(path), 1);
	envp = env_to_str(envp_data);
	execve(path, cmd_data->cmd, envp);
	ft_putstr_fd("minishell : ", STDERR);
	ft_putstr_fd(cmd_data->cmd[0], STDERR);
	ft_putendl_fd(" command not found.", STDERR);
	ft_free_arr(cmd_data->cmd);
	ft_free_arr(envp); 
	exit(1);
}
