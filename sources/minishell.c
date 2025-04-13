/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/04/13 18:35:39 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sig g_sig;

bool	init_data(t_data *data, char **envp)
{
	data->envp = get_env(envp);
	if (!data->envp)
	{
		error_message("Could not initialize environment", NULL, false);
		return (false);
	}
	data->user_input = NULL;
	data->work = true;
	data->token = NULL;
	data->cmd = NULL;
	data->exit_code = 0;
	return (true);
}

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
	pos = ft_strjoin(PROMPT1, folders[len - 1]);
	pos = ft_strjoin(pos, PROMPT2);
	ft_free_arr(folders);
	free(path);
	return (pos);
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;
	char	*path;

	(void)argc;
	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (!init_data(&data, envp))
		error_message("Could not initialize data", NULL, false);
	while (data.work)
	{
		path = get_path();
		set_signal_interactive();
		data.user_input = readline(path);
		set_signal_noninteractive();
		if (data.user_input == NULL)
			exit_shell(&data, EXIT_SUCCESS);
		parsing(&data);
		if (is_builtin(data.cmd))
		 	exec_buitlins(data.user_input, &data);
		else
			exec(&data);
		lst_clear_cmd(&data.cmd, &free_ptr);
		lst_clear_token(&data.token, &free_ptr);
	}
	return (data.exit_code);
}
