/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:56:52 by rureshet          #+#    #+#             */
/*   Updated: 2025/05/04 17:51:49 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

int	var_exists(t_data *data, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while (data->env_list[i])
	{
		if (ft_strncmp(data->env_list[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*extract_env_value(t_data *data, char *var)
{
	int		i;
	char	*value;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while (data->env_list[i])
	{
		if (ft_strncmp(data->env_list[i], var, len) == 0)
			break ;
		i++;
	}
	value = ft_strdup(data->env_list[i] + len);
	return (value);
}

char	*resolve_env_variable(t_token *token, char *str, t_data *data)
{
	char	*value;
	char	*name_var;

	name_var = search_name_var(str);
	if (name_var && var_exists(data, name_var) == 0)
	{
		if (token != NULL)
			token->var_exists = true;
		value = extract_env_value(data, name_var);
	}
	else if (name_var && name_var[0] == '?' && name_var[1] == '=')
		value = ft_itoa(data->exit_code);
	else
		value = NULL;
	free_ptr(name_var);
	return (value);
}

int	find_env_var_index(char **env, char *var)
{
	int		i;
	size_t	len;

	if (!var || !env)
		return (-1);
	len = ft_strlen(var);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(env[i], var, len) == 0 && env[i][len] == '=')
			return (i);
		i++;
	}
	return (-1);
}

char	*fetch_env_var_value(char **env, char *var)
{
	int		i;
	char	*tmp;

	tmp = ft_strjoin(var, "=");
	if (!tmp)
		return (NULL);
	i = 0;
	while (env[i])
	{
		if (ft_strncmp(tmp, env[i], ft_strlen(tmp)) == 0)
		{
			free_ptr(tmp);
			return (ft_strchr(env[i], '=') + 1);
		}
		i++;
	}
	free_ptr(tmp);
	return (NULL);
}
