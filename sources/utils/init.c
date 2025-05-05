/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   init.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/05 14:44:28 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/05 15:03:23 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

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
	data->cmd = NULL;
	data->pid = -1;
	data->exit_code = 0;
	return (true);
}
