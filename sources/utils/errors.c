/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:57 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/23 17:48:00 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_message(char *text_error)
{
	write(STDOUT_FILENO, "minishell: ", 11);
	ft_putstr_fd(text_error, STDERR_FILENO);
	printf("\n");
}
