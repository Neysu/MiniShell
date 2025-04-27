/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: rureshet <rureshet@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/24 17:47:29 by rureshet          #+#    #+#             */
/*   Updated: 2025/04/27 17:03:03 by rureshet         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../minishell.h"

void	signal_reset_prompt(int signal)
{
	(void)signal;
	write(1, "\n", 1);
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	signal_newline(int signal)
{
	(void)signal;
	rl_on_new_line();
}

void	set_signal_interactive(void)
{
	struct sigaction sig;

	signal_ignore_sigquit();
	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &signal_reset_prompt;
	sigaction(SIGINT, &sig, NULL);
}

void	set_signal_noninteractive(void)
{
	struct sigaction sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = &signal_newline;
	sigaction(SIGINT, &sig, NULL);
	sigaction(SIGQUIT, &sig, NULL);
}

void	signal_ignore_sigquit(void)
{
	struct sigaction sig;

	ft_memset(&sig, 0, sizeof(sig));
	sig.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sig, NULL);
}

