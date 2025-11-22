#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>

void	handle_sigint(int sig);
void	setup_interactive_parent_signals(void);
void	setup_parent_signals_before_execv(void);
void	setup_child_signals(void);

void	interactive_mode(void);
void	non_interactive_mode(void);

#endif