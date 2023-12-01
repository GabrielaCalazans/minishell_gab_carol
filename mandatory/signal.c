/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signal.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gacalaza <gacalaza@student.42sp.org.br     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2023/11/16 02:32:53 by gacalaza          #+#    #+#             */
/*   Updated: 2023/12/01 15:12:08 by gacalaza         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../include/minishell.h"

void	restore_prompt(int sig)
{
	// g_ret = 130;
	write(1, "\n", 1);
	rl_replace_line("", 0);
	rl_on_new_line();
	rl_redisplay();
	(void)sig;
}

void	ctrl_c(int sig)
{
	// g_ret = 130;
	write(1, "\n", 1);
	(void)sig;
}

void	back_slash(int sig)
{
	// g_ret = 131;
	(void)sig;
}

void	run_signals(int sig)
{
	if (sig == 1)
	{
		signal(SIGINT, restore_prompt);
		signal(SIGQUIT, SIG_IGN);
	}
	if (sig == 2)
	{
		signal(SIGINT, ctrl_c);
		signal(SIGQUIT, back_slash);
		// signal(SIGEOF, ctrl_d);
	}
	if (sig == 3)
	{
		printf("exit\n");
		exit(0);
	}
}
