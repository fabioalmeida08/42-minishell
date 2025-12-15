/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parser.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/12/15 13:53:45 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/15 14:41:10 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

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
