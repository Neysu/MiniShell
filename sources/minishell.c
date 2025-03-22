/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/21 21:50:30 by egibeaux         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

char	*get_path()
{
	char	**folders;
	char	*path;
	char	*pos;
	int		len;

	path = ft_calloc(sizeof(char), PATH_MAX_LEN);
	getcwd(path, PATH_MAX_LEN);
	folders = ft_split(path, '/');
	len = ft_arrlen(folders);
	pos = ft_strjoin(folders[len - 1], " > ");
	ft_free_arr(folders);
	free(path);
	return (pos);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*pos;
	t_data	*data;
	t_envp	*env_data;
	t_cmd	*cmd_data;

	(void)argc;
	(void)argv;
	data->work = true;
	env_data = get_env(envp);
	while (data->work)
	{
		pos = get_path();
		line = readline(pos);
		cmd_data = parse_cmd(line);
		if (is_builtin(line))
			exec_buitlins(line, env_data);
		else
			exec_cmd(cmd_data, env_data);
		free(pos);
	}
	ft_free_env(envp_data);
	return (0);
}
