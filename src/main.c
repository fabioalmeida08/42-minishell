/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:10:15 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/27 10:00:50 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	t_shell	shell_vars;

	(void)argc;
	(void)argv;
	init_env(envp, &shell_vars);
	if (isatty(STDIN_FILENO))
	{
		setup_interactive_parent_signals();
		interactive_mode();
	}
	else
		non_interactive_mode();
	return (0);
}
