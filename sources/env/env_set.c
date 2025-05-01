/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_set.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/05/01 18:24:46 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/01 18:26:02 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

static char	**realloc_env_vars(t_data *data, int size)
{
	char	**new_env;
	int		i;

	new_env = ft_calloc(size + 1, sizeof * new_env);
	if (!new_env)
		return (NULL);
	i = 0;
	while (data->env_list[i] && i < size)
	{
		new_env[i] = ft_strdup(data->env_list[i]);
		free_ptr(data->env_list[i]);
		i++;
	}
	free(data->env_list);
	return (new_env);
}

bool	set_env_var(t_data *data, char *key, char *value)
{
	int		idx;
	char	*tmp;

	idx = get_env_var_index(data->env_list, key);
	if (value == NULL)
		value = "";
	tmp = ft_strjoin("=", value);
	if (!tmp)
		return (false);
	if (idx != -1 && data->env_list[idx])
	{
		free_ptr(data->env_list[idx]);
		data->env_list[idx] = ft_strjoin(key, tmp);
	}
	else
	{
		idx = env_var_count(data->env_list);
		data->env_list = realloc_env_vars(data, idx + 1);
		if (!data->env_list)
			return (false);
		data->env_list[idx] = ft_strjoin(key, tmp);
	}
	free_ptr(tmp);
	return (true);
}

bool	remove_env_var(t_data *data, int idx)
{
	int	i;
	int	count;

	if (idx > env_var_count(data->env_list))
		return (false);
	free_ptr(data->env_list[idx]);
	i = idx;
	count = idx;
	while (data->env_list[i + 1])
	{
		data->env_list[i] = ft_strdup(data->env_list[i + 1]);
		free_ptr(data->env_list[i + 1]);
		count++;
		i++;
	}
	data->env_list = realloc_env_vars(data, count);
	if (!data->env_list)
		return (false);
	return (true);
}
