/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/24 23:28:02 by egibeaux         ###   ########.fr       */
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
	if (!ft_strncmp(path, "/", 1) && ft_strlen(path) == 1)
		pos = ft_strdup("/ > ");
	else
	{
		folders = ft_split(path, '/');
		len = ft_arrlen(folders);
		pos = ft_strjoin(folders[len - 1], " > ");
		ft_free_arr(folders);
	}
	free(path);
	return (pos);
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*pos;
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	data->work = true;
	data->ret = 0;
	data->env_data = get_env(envp);
	while (data->work)
	{
		pos = get_path();
		line = readline(pos);
		data->cmd_data = parse_cmd(line);
		if (is_builtin(line))
			exec_buitlins(line, data->env_data, data);
		else
			exec_cmd(data->cmd_data, data->env_data);
		free(pos);
	}
	ft_free_env(data->env_data);
	return (data->ret);
}

