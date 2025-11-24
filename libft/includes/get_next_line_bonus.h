/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fabialme <fabialme@student.42sp.org.br>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/07/25 16:34:50 by fabialme          #+#    #+#             */
/*   Updated: 2025/07/25 17:27:07 by fabialme         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif // !BUFFER_SIZE

# ifndef MAX_FD
#  define MAX_FD 1024
# endif // !MAX_FD

# include <stdlib.h>
# include <unistd.h>

char	*get_next_line(int fd);
void	*ft_calloc(size_t elmt_qtd, size_t elmt_size);
char	*join_and_free(char *s1, char *s2);
char	*ft_strchr(const char *s, char c);
size_t	ft_strlen(const char *s);
#endif // !GET_NEXT_LINE
