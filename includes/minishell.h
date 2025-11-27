/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/24 10:47:12 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/27 10:34:42 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

# define _DEFAULT_SOURCE
# include <unistd.h>
# include <stdlib.h>
# include <signal.h>
# include <stdio.h>
# include <readline/readline.h>
# include <readline/history.h>
# include <stdbool.h>
# include "../libft/includes/libft.h"
# include "./structs.h"

void	handle_sigint(int sig);
void	setup_interactive_parent_signals(void);
void	setup_child_signals(void);

void	init_env(char **envp, t_shell *shell_vars);
void	free_env_list(t_env *env_list);
t_env	*create_env_node(char *key, char *value);
int		append_env_list(t_env **head, t_env *new_node);

t_env	*get_env_node(t_env *env_list, char *key);
char	*get_env_value(t_env *env_list, char *key);
int		add_env_var(t_env **env_list, char *key, char *value);
int		update_env_var(t_env *env_list, char *key, char *value);
int		remove_env_var(t_env **env_list, char *key);

void	interactive_mode(void);
void	non_interactive_mode(void);

#endif
