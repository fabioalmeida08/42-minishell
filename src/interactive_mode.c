/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2025/11/25 10:17:08 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

void	interactive_mode(void)
{
	char	*input;

	while (1)
	{
		input = readline("Minishell> ");
		if (input == NULL)
		{
			free(input);
			break ;
		}
		add_history(input);
		printf("FOI DIGITADO: %s\n", input);

		ft_strtok(input, "s");
		free(input);
	}
}
