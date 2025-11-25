/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lexer_utils.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/11/25 11:48:32 by fabialme          #+#    #+#             */
/*   Updated: 2025/11/25 11:57:15 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../includes/lexer.h"

static bool check_quotes(const char *str)
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

t_token *ft_strtok(const char *str, char *delimiter)
{
	(void) *delimiter;
	t_token	*token;
	token = ft_calloc(1, sizeof(t_token));
	if (!check_quotes(str))
	{
		free(token);
		ft_putstr_fd("sytax error", 2);
		exit(1);
	}
	ft_printf("sem error\n");

	return (token);
}
