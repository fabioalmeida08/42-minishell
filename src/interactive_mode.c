/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   interactive_mode.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/22 14:32:35 by bolegari          #+#    #+#             */
/*   Updated: 2025/12/11 17:21:31 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/minishell.h"

void print_ast(t_ast *node, int depth)
{
    if (!node)
        return;

    // indentação
    for (int i = 0; i < depth; i++)
        printf("  ");

    // tipo do nó
    if (node->type == CMD_NODE)
    {
        printf("CMD_NODE: ");
        for (int i = 0; node->args[i]; i++)
            printf("%s ", node->args[i]);
        printf("\n");

        if (node->in)
            printf("%*sIN REDIR: %s\n", depth * 2 + 2, "", node->in->file);
        if (node->out)
            printf("%*sOUT REDIR: %s\n", depth * 2 + 2, "", node->out->file);
    }
    else if (node->type == PIPE_NODE)
    {
        printf("PIPE_NODE\n");
    }

    // recursão
    print_ast(node->left, depth + 1);
    print_ast(node->right, depth + 1);
}

t_token	*find_last_pipe(t_token *tokens)
{
	t_token	*last_pipe;
	t_token	*current;

	last_pipe = NULL;
	current = tokens;
	while (current)
	{
		if (current->type == TK_PIPE)
			last_pipe = current;
		current = current->next;
	}
	return (last_pipe);
}

t_ast	*parser_cmd(t_token *tokens)
{
	t_ast	*node;
	t_token	*current;
	int		argc;
	int		i;
	t_redirect	*redir;

	argc = 0;
	node = malloc(sizeof(t_ast));
	node->type = CMD_NODE;
	node->left = NULL;
	node->right = NULL;
	node->in = NULL;
	node->out = NULL;

	current = tokens;
	while (current)
	{
		if (current->type == TK_WORD)
			argc++;
		current = current->next;
	}

	node->args = malloc(sizeof(char *) * (argc + 1));
	current = tokens;
	i = 0;
	while (current)
	{
		if (current->type == TK_WORD)
		{
			node->args[i] = ft_strdup(current->value);
			i++;
		}
		else if (current->type == TK_REDIR_IN || current->type == TK_REDIR_OUT || 
			current->type == TK_REDIR_APPEND ||current->type == TK_REDIR_HEREDOC)
		{
			redir = malloc(sizeof(t_redirect));
			redir->type = current->type;
			if (current->next)
				redir->file = ft_strdup(current->next->value);
			redir->content = NULL; //usado apenas para heredoc
			if (current->type == TK_REDIR_IN || current->type == TK_REDIR_HEREDOC)
				node->in = redir;
			else
				node->out = redir;
			current = current->next;
		}
		current = current->next;
	}
	node->args[i] = NULL;
	return (node);
}

t_ast	*parser_ast(t_token *tokens)
{
	t_token	*last_pipe;
	t_token	*right_tokens;
	t_token	*left_tokens;
	t_token	*prev;
	t_ast	*node;

	last_pipe = find_last_pipe(tokens);
	if (!last_pipe)
		return (parser_cmd(tokens));
	right_tokens = last_pipe->next;
	prev = tokens;
	while (prev && (prev->next != last_pipe))
		prev = prev->next;
	if (prev)
		prev->next = NULL;
	left_tokens = tokens;
	node = malloc(sizeof(t_ast));
	node->type = PIPE_NODE;
	node->left = parser_ast(left_tokens);
	node->right = parser_ast(right_tokens);
	return (node);
}

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
