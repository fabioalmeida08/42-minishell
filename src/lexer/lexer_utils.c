/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:48:32 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/01 11:58:23 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool check_syntax(const char *str)
{
	bool in_single;
	bool in_double;
	bool escaped;

	in_single = false;
	in_double = false;
	escaped = false;
	while (*str)
	{
		if (escaped)
		{
			escaped = false;
			str++;
			continue ;
		}
		if (*str == '\\')
			escaped = true;
		else if (*str == '\'' && !in_double)
			in_single = !in_single;
		else if (*str == '\"' && !in_single)
			in_double = !in_double;
		str++;
	}
	return (!in_single && !in_double && !escaped);
}

// t_token	*split_tokens(char *str)
// {
// 	//echo "texto" > "file.txt"
// 	t_token	*token;
// }

t_token	*ft_tokenize(const char *str, t_shell *sh)
{
	t_token	*token;

	token = NULL;
	if (!check_syntax(str))
		return (lexer_syntax_error(token, sh));
	return (NULL);
}



// static bool	is_operator_char(char c)
// {
// 	return (c == '|' || c == '<' || c == '>');
// }


// static char	*extract_word(const char **str)
// {
// 	const char	*start;
// 	size_t		len;
// 	char		quote;
//
// 	start = *str;
// 	len = 0;
// 	quote = 0;
// 	while ((*str)[len])
// 	{
// 		if (quote == 0 && ((*str)[len] == '\'' || (*str)[len] == '"'))
// 			quote = (*str)[len];
// 		else if (quote && (*str)[len] == quote)
// 			quote = 0;
// 		else if (!quote && (is_whitespace((*str)[len])
// 				|| is_operator_char((*str)[len])))
// 			break ;
// 		len++;
// 	}
// 	*str += len;
// 	return (ft_strndup(start, len));
// }
//
// static t_token	*handle_operator(const char **str)
// {
// 	t_token_type	type;
// 	char			*value;
//
// 	if (**str == '|')
// 	{
// 		type = TOKEN_PIPE;
// 		value = ft_strndup(*str, 1);
// 		(*str)++;
// 	}
// 	else if (**str == '<' && *(*str + 1) == '<')
// 	{
// 		type = TOKEN_REDIR_HEREDOC;
// 		value = ft_strndup(*str, 2);
// 		(*str) += 2;
// 	}
// 	else if (**str == '>' && *(*str + 1) == '>')
// 	{
// 		type = TOKEN_REDIR_APPEND;
// 		value = ft_strndup(*str, 2);
// 		(*str) += 2;
// 	}
// 	else if (**str == '<')
// 	{
// 		type = TOKEN_REDIR_IN;
// 		value = ft_strndup(*str, 1);
// 		(*str)++;
// 	}
// 	else
// 	{
// 		type = TOKEN_REDIR_OUT;
// 		value = ft_strndup(*str, 1);
// 		(*str)++;
// 	}
// 	return (create_token(type, value));
// }
//
//
// t_token	*ft_strtok(const char *str, t_shell *sh)
// {
// 	t_token	*tokens;
// 	t_token	*new_token;
// 	char	*word;
//
// 	tokens = NULL;
// 	if (!check_syntax(str))
// 		return (lexer_syntax_error(sh));
// 	while (*str)
// 	{
// 		while (is_whitespace(*str))
// 			str++;
// 		if (*str == '\0')
// 			break ;
// 		if (is_operator_char(*str))
// 		{
// 			new_token = handle_operator(&str);
// 			add_token_back(&tokens, new_token);
// 		}
// 		else
// 		{
// 			word = extract_word(&str);
// 			if (word && *word)
// 			{
// 				new_token = create_token(TOKEN_WORD, word);
// 				add_token_back(&tokens, new_token);
// 			}
// 			else
// 				free(word);
// 		}
// 	}
// 	return (tokens);
// }
