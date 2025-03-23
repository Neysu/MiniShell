/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   exec.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: elliot <elliot@student.42.fr>              +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/07 04:17:29 by elliot            #+#    #+#             */
/*   Updated: 2025/03/23 17:41:08 by elliot           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"
#include <sys/types.h>
#include <sys/wait.h>
#include <unistd.h>

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

int		open_out(char *file, t_cmd *cmd_data)
{
	cmd_data->outfile = open(file, O_WRONLY | O_CREAT | O_TRUNC, 0644);
	if (cmd_data->outfile == -1)
		return (1);
	dup2(cmd_data->outfile, STDOUT_FILENO);
	close(cmd_data->outfile);
	return (0);
}

int	redirect_out(t_cmd *cmd_data)

{
	if (pipe(cmd_data->pipefd) == -1)
		return (1);
	if (open_out(cmd_data->file, cmd_data))
		return (1);
	if (dup2(cmd_data->pipefd[1], STDOUT_FILENO) == -1)
		return (1);
	(close(cmd_data->pipefd[0]), close(cmd_data->pipefd[1]));
	return (0);
}

int		open_inf(char *file, t_cmd *cmd_data)
{
	cmd_data->infile = open(file, O_RDONLY);
	if (cmd_data->infile == -1)
		return (ft_putendl_fd("NOP", 2), 1);
	dup2(cmd_data->infile, STDIN_FILENO);
	close(cmd_data->infile);
	return (0);
}

int	redirect_inf(t_cmd *cmd_data)
{
	if (open_inf(cmd_data->file, cmd_data))
		return (1);
	if (dup2(cmd_data->pipefd[1], STDOUT_FILENO) == -1)
		return (1);
	(close(cmd_data->pipefd[1]), close(cmd_data->pipefd[0]));
	return (0);
}

int	exec_cmd(t_cmd *cmd_data, t_envp *envp_data)
{
	char	*path;
	char	**envp;
	int		status;
	pid_t	pid;

	pipe(cmd_data->pipefd);

	pid = fork();
	if (pid == -1)
		exit(0);
	if (pid == 0)
	{
		open_inf(cmd_data->file, cmd_data);
		path = findcmd(cmd_data, envp_data);
		if (!path)
			error_path(cmd_data->cmd[0]);
		envp = env_to_str(envp_data);
		if (execve(path, cmd_data->cmd, envp) == -1)
			(ft_printf(ERRORCMD, cmd_data->cmd[0]), ft_free_arr(cmd_data->cmd), ft_free_arr(envp), exit(1));
	}
	else
		waitpid(pid, &status, 0);
	return (0);
}
