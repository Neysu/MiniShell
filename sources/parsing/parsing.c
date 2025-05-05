/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/08 02:35:57 by elliot            #+#    #+#             */
/*   Updated: 2025/05/05 12:12:57 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

bool	parser_user_input(t_data *data)
{
	if (ft_strcmp(data->user_input, "\0") == 0)
		return (false);
	else if (input_is_space(data->user_input))
		return (true);
	add_history(data->user_input);
	if (token_generator(data, data->user_input) == FAILURE)
		return (false);
	if (data->token->type == END)
		return (false);
	if (envp_check(&data->token) == FAILURE)
		return (false);
	var_expander(data, &data->token);
	quotes_handler(data);
	create_commands(data, data->token);
	return (true);
}
