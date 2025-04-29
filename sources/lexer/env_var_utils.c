/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   env_var_utils.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/28 20:03:01 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/28 20:03:15 by rureshet         ###   ########.fr       */
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
