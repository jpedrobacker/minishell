/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbergfel <jbergfel@student.42.rio>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2024/07/08 16:11:29 by jbergfel          #+#    #+#             */
/*   Updated: 2024/07/10 17:11:59 by jbergfel         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../inc/minishell.h"

void	sig_int_handle(int sig)
{
	int	sig_proc;

	sig_proc = 0;
	if (sig == SIGUSR1)
		sig_proc = 0;
	else if (sig == SIGUSR2)
		sig_proc = 1;
	if (sig == SIGINT)
	{
		if (!sig_proc)
		{
			write(1, "\n", 1);
			rl_on_new_line();
			rl_replace_line("", 0);
			rl_redisplay();
			g_status = 130;
		}
		else
			write(1, "\n", 1);
	}
}

void	sigs_handle(void)
{
	signal(SIGINT, sig_int_handle);
	signal(SIGUSR1, sig_int_handle);
	signal(SIGUSR2, sig_int_handle);
	signal(SIGQUIT, SIG_IGN);
}
