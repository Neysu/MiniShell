/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_handling.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/17 18:56:52 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/27 14:03:43 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	update_status(t_token **token, char c)
{
	if (c == '\'' && (*token)->type == DEFAULT)
		(*token)->type = SQUOTE;
	else if (c == '\"' && (*token)->type == DEFAULT)
		(*token)->type = DQUOTE;
	else if (c == '\'' && (*token)->type == SQUOTE)
		(*token)->type = DEFAULT;
	else if (c == '\"' && (*token)->type == DQUOTE)
		(*token)->type = DEFAULT;
}

int	var_exist(t_data *data, char *var)
{
	int	i;
	int	len;

	i = 0;
	len = ft_strlen(var);
	while(data->env_list[i])
	{
		if (ft_strncmp(data->env_list[i], var, len) == 0)
			return (0);
		i++;
	}
	return (1);
}

char	*get_env_value(t_data *data, char *var)
{
	int		i;
	char	*value;
	int		len;

	i = 0;
	len = ft_strlen(var);
	while(data->env_list[i])
	{
		if (ft_strncmp(data->env_list[i], var, len) == 0)
			break ;
		i++;
	}
	value = ft_strdup(data->env_list[i] + len);
	return (value);
}

char	*get_var_value(t_token *token, char *str, t_data *data)
{
	char 	*value;
	char	*name_var;

	name_var = search_name_var(str);
	if (name_var && var_exist(data, name_var) == 0)
	{
		if (token != NULL)
			token->var_exist = true;
		value = get_env_value(data, name_var);
	}
	else if (name_var && name_var[0] == '?' && name_var[1] == '=')
	{
		value = ft_itoa(data->exit_code);
	}
	else
		value = NULL;
	free_ptr(name_var);
	return (value);
}

int	exchange_var(t_token **token, char *var_value, int index)
{
	if (var_value == NULL)
	{
		if (erase_var(token, (*token)->str, index) == 1)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	else
	{
		if (erase_and_replace(token, (*token)->str, var_value, index) == NULL)
		{
			free_ptr(var_value);
			return (1);
		}
	}
	free_ptr(var_value);
	return (0);
}

int	get_env_var_index(char **env, char *var)
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
