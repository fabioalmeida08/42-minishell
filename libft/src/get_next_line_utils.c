/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 09:44:22 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/25 12:12:47 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */
#include "get_next_line.h"

size_t	ft_strlen(const char *s)
{
	size_t	len;

	len = 0;
	while (s[len])
		len++;
	return (len);
}

void	*ft_calloc(size_t elmt_qdt, size_t elmt_size)
{
	void			*mem;
	unsigned char	*tmp;
	size_t			i;

	if (!elmt_qdt || !elmt_size)
		return (malloc(1));
	if (elmt_size && elmt_qdt > (size_t) - 1 / elmt_size)
		return (NULL);
	mem = malloc(elmt_qdt * elmt_size);
	if (!mem)
		return (NULL);
	tmp = (unsigned char *) mem;
	i = 0;
	while (i < (elmt_qdt * elmt_size))
		tmp[i++] = '\0';
	return (mem);
}

char	*ft_strjoin(const char *s1, const char *s2)
{
	size_t	s1_len;
	size_t	s2_len;
	char	*str;
	char	*str_start;

	if (!s1 || !s2)
		return (NULL);
	s1_len = ft_strlen(s1);
	s2_len = ft_strlen(s2);
	str = ft_calloc((s1_len + s2_len + 1), sizeof(char));
	if (!str)
		return (NULL);
	str_start = str;
	while (*s1)
		*str_start++ = *s1++;
	while (*s2)
		*str_start++ = *s2++;
	return (str);
}

char	*ft_strchr(const char *s, char c)
{
	if (!s)
		return (NULL);
	while (*s)
	{
		if (*s == c)
			return ((char *) s);
		s++;
	}
	if (*s == c && c == '\0')
		return ((char *) s);
	return (NULL);
}
