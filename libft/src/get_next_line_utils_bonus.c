/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:38:07 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/25 17:27:54 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line_bonus.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t elmt_qtd, size_t elmt_size)
{
	void			*mem;
	size_t			i;
	unsigned char	*tmp;

	if (!elmt_qtd || !elmt_size)
		return (malloc(1));
	if (elmt_size && elmt_qtd > (size_t) - 1 / elmt_size)
		return (NULL);
	mem = malloc(elmt_qtd * elmt_size);
	if (!mem)
		return (NULL);
	tmp = (unsigned char *) mem;
	i = 0;
	while (i < (elmt_qtd * elmt_size))
		tmp[i++] = '\0';
	return (mem);
}

char	*join_and_free(char *s1, char *s2)
{
	ssize_t	i;
	size_t	j;
	char	*n_str;
	size_t	s1_len;
	size_t	s2_len;

	i = -1;
	j = 0;
	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	n_str = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!n_str)
		return (NULL);
	while (s1[++i])
		n_str[i] = s1[i];
	while (s2[j])
		n_str[i++] = s2[j++];
	free(s1);
	return (n_str);
}

char	*ft_strchr(const char *s, char c)
{
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (*s == c)
		return ((char *) s);
	return (NULL);
}
