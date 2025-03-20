/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/20 16:45:57 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/20 16:56:55 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	error_message(char *text_error)
{
	printf("Minishell Error: ");
	ft_putstr_fd(text_error, STDERR_FILENO);
	printf("\n");
}
