/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer.h                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:32:06 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/01 11:35:42 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEXER_H
# define LEXER_H

# include "../libft/includes/libft.h"
# include "./minishell.h"

typedef enum e_token_type
{
	TK_WORD,
	TK_PIPE,
  TK_AND,
	TK_OR,
  TK_PAREN_OPEN,
	TK_PAREN_CLOSE,
	TK_REDIR_IN,
	TK_REDIR_OUT,
	TK_REDIR_APPEND,
	TK_REDIR_HEREDOC,
	TK_EOF
}	t_token_type;

typedef struct s_token
{
	char			*value;
	t_token_type	type;
	struct s_token	*next;
}	t_token;

t_token	*ft_tokenize(const char *str, t_shell *sh);
void	*lexer_syntax_error(t_token *token, t_shell *sh);
#endif // !LEXER_H
