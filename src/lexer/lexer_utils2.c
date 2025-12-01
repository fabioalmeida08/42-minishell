/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils2.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/26 14:27:57 by fabialme          #+#    #+#             */
/*   Updated: 2025/12/01 11:33:52 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

void	*lexer_syntax_error(t_token *token, t_shell *sh)
{
	free(token);
	ft_putstr_fd("Sytax error\n", 2);
	sh->exit_status = 2;
	return (NULL);
}
