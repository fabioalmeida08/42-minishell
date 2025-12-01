/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/01 11:35:31 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"
#include "../includes/lexer.h"

void	interactive_mode(t_shell *sh)
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
		ft_tokenize(input, sh);
		free(input);
	}
}
