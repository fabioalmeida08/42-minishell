/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/15 14:40:52 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void	interactive_mode(t_shell *sh)
{
	char	*input;
	t_ast	*ast;

	while (1)
	{
		input = readline("Minishell> ");
		if (input == NULL)
		{
			free(input);
			break ;
		}
		add_history(input);
		sh->head_tokens = ft_tokenize(input, sh);
		ast = parser_ast(sh->head_tokens);
		print_ast(ast, 1);
		/*
		char **input_splited = ft_split(input, ' ');
		if (is_builtin(input_splited, sh))
			exec_builtin(input_splited, sh);
		else
			execve_cmd(input_splited, sh);
		free_envp(input_splited);
		*/
		ft_free_tokens(sh->head_tokens);
		sh->head_tokens = NULL;
		free(input);
	}
	ft_free_tokens(sh->head_tokens);
	free(sh->g_builtins);
	free_env_list(sh->env_list);
}
