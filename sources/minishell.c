/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/06 23:16:12 by egibeaux          #+#    #+#             */
/*   Updated: 2025/05/03 19:07:51 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../minishell.h"

t_sig	g_sig;

static bool	start_check(int argc)
{
	if (argc != 1)
	{
		ft_putendl_fd("Usage: ./minishell\n", 2);
		return (false);
	}
	return (true);
}

static bool	init_env(t_data *data, char **env)
{
	int		i;

	data->env_list = ft_calloc(env_var_count(env) + 1, sizeof * data->env_list);
	if (!data->env_list)
		return (false);
	i = 0;
	while (env[i])
	{
		data->env_list[i] = ft_strdup(env[i]);
		if (!data->env_list[i])
			return (false);
		i++;
	}
	return (true);
}

static bool	init_wds(t_data *data)
{
	char	buff[PATH_MAX_LEN];
	char	*wd;

	wd = getcwd(buff, PATH_MAX_LEN);
	data->working_dir = ft_strdup(wd);
	if (!data->working_dir)
		return (false);
	if (find_env_var_index(data->env_list, "OLDPWD") != -1)
	{
		data->old_working_dir = ft_strdup(fetch_env_var_value(data->env_list,
					"OLDPWD"));
		if (!data->old_working_dir)
			return (false);
	}
	else
	{
		data->old_working_dir = ft_strdup(wd);
		if (!data->old_working_dir)
			return (false);
	}
	return (true);
}

bool	init_data(t_data *data, char **envp)
{
	if (!init_env(data, envp))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize environment", 1);
		return (false);
	}
	if (!init_wds(data))
	{
		errmsg_cmd("Fatal", NULL, "Could not initialize working directories",
			1);
		return (false);
	}
	data->token = NULL;
	data->user_input = NULL;
	data->work = true;
	data->cmd = NULL;
	data->pid = -1;
	data->exit_code = 0;
	return (true);
}

void	minishell(t_data *data)
{
	char	**user_input;
	int		i;

	while (1)
	{
		set_signal_interactive();
		data->user_input = readline(PROMPT);
		set_signal_noninteractive();
		if (data->user_input == NULL)
			print_exit_shell(data, data->exit_code);
		user_input = ft_split(data->user_input, ';');
		if (!user_input)
			exit_shell(data, EXIT_FAILURE);
		i = 0;
		while (user_input[i])
		{
			data->user_input = ft_strdup(user_input[i]);
			if (parser_user_input(data) == true)
			{
				show_lists(data);
				data->exit_code = execute(data);
			}
			else
				data->exit_code = 1;
			i++;
			free_data(data, false);
		}
		free_str_tab(user_input);
	}
}

int	main(int argc, char **argv, char **envp)
{
	t_data	data;

	(void)argv;
	ft_memset(&data, 0, sizeof(t_data));
	if (!start_check(argc) || !init_data(&data, envp))
		exit_shell(NULL, EXIT_FAILURE);
	minishell(&data);
	exit_shell(&data, data.exit_code);
	return (0);
}
