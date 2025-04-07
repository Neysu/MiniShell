/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   expand_variables.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/28 19:15:16 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/31 16:54:04 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void 	update_status(t_token **token, char c)
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

bool	char_is_sep(char c)
{
	if (c == '$' || c == ' ' || c == '=' || c == '\0')
		return (true);
	else
		return (false);
}

bool	between_quotes(char *str, int i)
{
	if (i > 0)
	{
		if (str[i - 1] == '\'' || str[i + 1] == '\'' || str[0] == '\'')
			return (true);
		else
			return (false);
	}
	return (false);
}

bool	is_var_valid(char c)
{
	if (ft_isalnum(c) == 0 && c != '_')
		return (false);
	else
		return (true);
}

int	var_len(char *str)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	while (str[i] != '$')
		i++;
	i++;
	if ((str[i] >= '0' && str[i] <= '9') || str[i] == '?')
		return (count + 1);
	while (str[i])
	{
		if (is_var_valid(str[i]) == false)
			break ;
		count++;
		i++;
	}
	return (count);
}

char	*search_name_var(char *str)
{
	char	*var;
	char	*tmp;
	int		len;
	int		start;
	int		i;
	i = 0;
	start  = 0;
	while (str[i])
	{
		if (str[i] == '$')
		{
			start = i + 1;
			break ;
		}
		i++;
	}
	len = var_len(str);
	var = ft_substr(str, start, len);
	if (!var)
		return (NULL);
	tmp = ft_strjoin(var, "=");
	free(var);
	var = tmp;
	return (var);
}

int	var_exist(t_data *data, char *var)
{
	t_envp *temp;
	int	len;

	len = ft_strlen(var);
	temp = data->envp;
	while(temp)
	{
		if (ft_strncmp(temp->var, var, len) == 0)
			return (0);
		temp = temp->next;
	}
	return (1);
}

char	*get_env_value(t_data *data, char *var)
{
	t_envp	*temp;
	char	*value;
	int		len;

	len = ft_strlen(var);
	temp = data->envp;
	while(temp)
	{
		if (ft_strncmp(temp->var, var, len) == 0)
			break ;
		temp = temp->next;
	}
	value = ft_strdup(temp->var + len);
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

int	erase_var(t_token **token, char *str, int index)
{
	int		i;
	int		j;
	int		len;
	char	*new_str;

	i = 0;
	j = 0;
	len = ft_strlen(str) - var_len(str + index);
	new_str = malloc(sizeof(char) * len + 1);
	if (!new_str)
		return (1);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			i += var_len(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[i] = '\0';
	free_ptr((*token)->str);
	(*token)->str = new_str;
	return (0);
}

void	copy_var_value(char *new_str, char *var_value, int *j)
{
	int	k;

	k = 0;
	while (var_value[k])
	{
		new_str[*j] = var_value[k];
		k++;
		(*j)++;
	}
}

char	*get_new_token_str(char *str, char *var_value, int new_str_size, int index)
{
	int		i;
	int		j;
	char	*new_str;

	i = 0;
	j = 0;
	new_str = malloc(sizeof(char) * new_str_size);
	if (!new_str)
		return (NULL);
	while (str[i])
	{
		if (str[i] == '$' && i == index)
		{
			copy_var_value(new_str, var_value, &j);
			i = i + var_len(str + index) + 1;
			if (str[i] == '\0')
				break ;
		}
		new_str[j++] = str[i++];
	}
	new_str[j] = '\0';
	return (new_str);
}

char	*erase_and_replace(t_token **token, char *str, char *var_value, int index)
{
	char	*new_str;
	int		new_str_size;

	new_str_size = (ft_strlen(str) - var_len(str + index) + ft_strlen(var_value));
	new_str = get_new_token_str(str, var_value, new_str_size, index);
	if (token && *token)
	{
		free_ptr((*token)->str);
		(*token)->str = new_str;
	}
	return (new_str);
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

int	expand_variables(t_data *data, t_token **tokens)
{
	t_token	*temp;
	int		i;

	temp = *tokens;
	while (temp)
	{
		if (temp->type == ENV)
		{
			i = 0;
			while (temp->str[i])
			{
				update_status(&temp, temp->str[i]);
				if (temp->str[i] == '$' && char_is_sep(temp->str[i + 1]) == false
					&& between_quotes(temp->str, i) == false
					&& (temp->status == DEFAULT || temp->status == DQUOTE))
					exchange_var(&temp, get_var_value(temp, temp->str + i, data), i);
				else
					i++;
			}
		}
		temp = temp->next;
	}
	return (0);
}
