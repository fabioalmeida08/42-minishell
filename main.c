/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/17 16:10:15 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/22 15:38:18 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "minishell.h"

//gcc -Wall -Wextra -Werror main.c interactive_mode.c non_interactive_mode.c signals.c -lreadline

int	main(int argc, char *argv[], char *envp[])
{
	(void)argc;
	(void)argv;
	(void)envp;

	if (isatty(STDIN_FILENO))
	{
		setup_interactive_parent_signals();
		interactive_mode();
	}
	else
		non_interactive_mode();
	
	return (0);
}
