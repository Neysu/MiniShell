/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:47:29 by rureshet          #+#    #+#             */
/*   Updated: 2025/03/24 19:07:36 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	sig_int(int code)
{
	(void)code;
	if (g_sig.pid == 0)
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(PROMPT, STDERR);
		g_sig.exit_status = 1;
	}
	else
	{
		ft_putstr_fd("\n", STDERR);
		ft_putstr_fd(PROMPT, STDERR);
		g_sig.exit_status = 130;
	}
	g_sig.sigint = 1;
}

void	sig_quit(int code)
{
	char	*num;

	num = ft_itoa(code);
	if (g_sig.pid != 0)
	{
		ft_putstr_fd("Quit: ", STDERR);
		ft_putendl_fd(num, STDERR);
		g_sig.exit_status = 131;
		g_sig.sigquit = 1;
	}
	else
		ft_putstr_fd("\b\b \b\b", STDERR);
}

void	siginit(void)
{
	g_sig.exit_status = 0;
	g_sig.pid = 0;
	g_sig.sigint = 0;
	g_sig.sigquit = 0;
}
