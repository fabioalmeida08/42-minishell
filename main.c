/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:10:15 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/17 16:10:18 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gcc -Wall -Wextra -Werror main.c -lreadline

void	handle_sigint(int sig)
{
	(void)sig;
	printf("\n");
	rl_on_new_line();
	rl_replace_line("", 0);
	rl_redisplay();
}

void	setup_parent_signals()
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

int	main()
{
	char	*input;
	
	setup_parent_signals();
	while (1)
	{
		input = readline("Minishell> ");
		if (input == NULL)
		{
			free(input);
			break;
		}
		add_history(input);
		printf("FOI DIGITADO: %s\n", input);
		free(input);
	}
	return (0);
}
