/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_pipe.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/04/25 11:50:38 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/25 11:54:31 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	parse_pipe(t_cmd **cmd, t_token **token_lst)
{
	t_cmd	*last_cmd;

	last_cmd = lst_last_cmd(*cmd);
	last_cmd->pipe_output = true;
	lst_addback_cmd(&last_cmd, lst_new_cmd(false));
	*token_lst = (*token_lst)->next;
}
