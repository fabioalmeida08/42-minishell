/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:10:15 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/24 20:14:49 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	t_shell	shell_vars;
	
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
