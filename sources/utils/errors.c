/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:57 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/23 21:11:36 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

char	*str_join(char *str, char *add)
{
	char	*tmp;

	if (!add)
		return (str);
	if (!str)
		return (ft_strdup(add));
	tmp = str;
	str = ft_strjoin(tmp, add);
	free(tmp);
	return (str);
}

static bool	add_detail_quotes(char *command)
{
	if (ft_strncmp(command, "export", 7) == 0
		|| ft_strncmp(command, "unset", 6) == 0)
		return (true);
	return (false);
}

int	errmsg_cmd(char *command, char *detail, char *error_message, int error_nb)
{
	char	*msg;
	bool	detail_quotes;

	detail_quotes = add_detail_quotes(command);
	msg = ft_strdup("minishell: ");
	if (command != NULL)
	{
		msg = str_join(msg, command);
		msg = str_join(msg, ": ");
	}
	if (detail != NULL)
	{
		if (detail_quotes)
			msg = str_join(msg, "`");
		msg = str_join(msg, detail);
		if (detail_quotes)
			msg = str_join(msg, "'");
		msg = str_join(msg, ": ");
	}
	msg = str_join(msg, error_message);
	ft_putendl_fd(msg, STDERR_FILENO);
	free_ptr(msg);
	return (error_nb);
}

void	error_message(char *text_error, char *detail, int quote)
{
	char	*messsage;

	messsage = ft_strdup("minishell: ");
	messsage = str_join(messsage, text_error);
	if (quote)
		messsage = str_join(messsage, " `");
	else
		messsage = str_join(messsage, " : ");
	messsage = str_join(messsage, detail);
	if (quote)
		messsage = str_join(messsage, "'");
	messsage = str_join(messsage, "\n");
	ft_putstr_fd(messsage, STDERR);
	free_ptr(messsage);
}
