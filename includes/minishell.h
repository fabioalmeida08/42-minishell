/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:47:12 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/01 10:30:12 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"

typedef struct s_env
{
	char			*key;
	char			*value;
	struct s_env	*next;	
}	t_env;

typedef struct s_shell
{
	char	**envp;
	t_env	*env_list;
	int	exit_status;
}	t_shell;

void	handle_sigint(int sig);
void	setup_interactive_parent_signals(void);
void	setup_child_signals(void);

void	init_env(char **envp, t_shell *shell_vars);
t_env	*get_key_env_list(t_env *env_list, char *str);
void	free_env_list(t_env *env_list);

void	interactive_mode(t_shell *sh);
void	non_interactive_mode(void);

#endif
