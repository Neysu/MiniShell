/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:57 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/15 17:58:10 by rureshet         ###   ########.fr       */
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
