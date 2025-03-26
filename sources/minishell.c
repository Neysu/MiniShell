/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: egibeaux <egibeaux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/03/26 02:32:06 by egibeaux         ###   ########.fr       */
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

void	ft_free_token(t_token *token)
{
	t_token	*tmp;

	while (token)
	{
		tmp = token->next;
		free(token);
		token = tmp;
	}
}

int	main(int argc, char **argv, char **envp)
{
	char	*line;
	char	*pos;
	t_data	*data;

	(void)argc;
	(void)argv;
	data = ft_calloc(sizeof(t_data), 1);
	data->cmd_data = ft_calloc(sizeof(t_cmd), 1);
	data->work = true;
	data->ret = 0;
	data->envp = get_env(envp);
	while (data->work)
	{
		pos = get_path();
		line = readline(pos);
		parsing(line, data);
		data->cmd_data->cmd = get_cmd(data->token);
		if (is_builtin(line))
			exec_buitlins(line, data);
		else
			exec_cmd(data->cmd_data, data->envp);
		free(pos);
		ft_free_arr(data->cmd_data->cmd);
		ft_free_token(data->token);
	}
	ft_free_env(data->envp);
	return (data->ret);
}

