/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: bolegari <bolegari@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:48:32 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/11 16:18:51 by bolegari         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/minishell.h"

void	*lexer_syntax_error(t_token *token, t_shell *sh)
{
	if (token)
	{
		free(token->value);
		free(token);
	}
	ft_putstr_fd("Syntax error\n", 2);
	sh->exit_status = 2;
	return (NULL);
}

static bool	check_syntax(const char *str)
{
	bool	in_single;
	bool	in_double;
	bool	escaped;

	in_single = false;
	in_double = false;
	escaped = false;
	while (*str)
	{
		if (escaped)
			escaped = false;
		if (*str == '\\' && !in_single)
			escaped = true;
		else if (*str == '\'' && !in_double)
			in_single = !in_single;
		else if (*str == '\"' && !in_single)
			in_double = !in_double;
		str++;
	}
	return (!in_single && !in_double && !escaped);
}

static char	*extract_word(const char **str)
{
	const char	*start;
	size_t		len;
	char		quote;
	char		c;

	start = *str;
	len = 0;
	quote = 0;
	if (!str || !*str || **str == 0)
		return (NULL);
	while ((*str)[len])
	{
		c = (*str)[len];
		if (quote == 0)
		{
			if (c == '\'' || c == '"')
			{
				quote = c;
				len++;
				continue ;
			}
			else if (ft_is_whitespace(c) || (c == '|' || c == '<' || c == '>'))
				break ;
		}
		else
		{
			if (c == quote)
			{
				quote = 0;
				len++;
				continue ;
			}
			else if (c == '\\' && quote == '"')
			{
				len++;
				if ((*str)[len])
					len++;
				continue ;
			}
		}
		len++;
	}
	*str += len;
	if (len == 0)
		return (NULL);
	return (ft_strndup(start, len));
}

static t_token	*handle_operator(const char **str)
{
	t_token_type	type;
	char			*value;
	size_t			len;

	if (!str || !*str || **str == '\0')
		return (NULL);
	len = 1;
	if (**str == '|')
		type = TK_PIPE;
	else if (**str == '<' && *(*str + 1) == '<')
	{
		type = TK_REDIR_HEREDOC;
		len = 2;
	}
	else if (**str == '>' && *(*str + 1) == '>')
	{
		type = TK_REDIR_APPEND;
		len = 2;
	}
	else if (**str == '<')
		type = TK_REDIR_IN;
	else
		type = TK_REDIR_OUT;
	value = ft_strndup(*str, len);
	if (!value)
		return (NULL);
	*str += len;
	return (create_token(type, value));
}

t_token	*ft_strtok(const char *str, t_shell *sh)
{
	t_token	*tokens;
	t_token	*new_token;
	char	*word;

	tokens = NULL;
	if (!str || !check_syntax(str))
		return (lexer_syntax_error(tokens, sh));
	while (*str)
	{
		while (ft_is_whitespace(*str))
			str++;
		if (*str == '\0')
			break ;
		if ((*str == '|' || *str == '<' || *str == '>'))
		{
			new_token = handle_operator(&str);
			if (!new_token)
				return (lexer_syntax_error(tokens, sh));
			add_token_back(&tokens, new_token);
		}
		else
		{
			word = extract_word(&str);
			if (word)
			{
				new_token = create_token(TK_WORD, word);
				if (!new_token)
				{
					free(word);
					return (lexer_syntax_error(tokens, sh));
				}
				add_token_back(&tokens, new_token);
			}
		}
	}
	return (tokens);
}

t_token	*ft_tokenize(const char *str, t_shell *sh)
{
	t_token	*tokens;

	tokens = NULL;
	if (!check_syntax(str))
		return (lexer_syntax_error(tokens, sh));
	tokens = ft_strtok(str, sh);
	if (!tokens)
		return (NULL);
	print_tokens(tokens);
	return (tokens);
}
