/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   signals.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:27:46 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/22 14:39:59 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gcc -Wall -Wextra -Werror main.c -lreadline

void	handle_sigint(int sig)
{
	if (sig == SIGINT)
	{
		printf("\n");
		rl_on_new_line();
		rl_replace_line("", 0);
		rl_redisplay();
	}
}

void	setup_parent_signals(void)
{
	struct sigaction	sa;

	sa.sa_handler = handle_sigint;
	sigemptyset(&sa.sa_mask);
	sa.sa_flags = SA_RESTART;
	sigaction(SIGINT, &sa, NULL);
	
	sa.sa_handler = SIG_IGN;
	sigaction(SIGQUIT, &sa, NULL);

	/*
	Restaura o comportamento padrão dos sinais quando for realizar os processos filhos
    	signal(SIGINT, SIG_DFL);
		signal(SIGQUIT, SIG_DFL);
		ANTES DO EXECV
		execve(path, args, envp);
	*/
}