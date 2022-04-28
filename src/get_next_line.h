/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:36:47 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/28 14:05:48 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdbool.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 1024
# endif

char		*get_next_line(int fd);

typedef struct s_lstring {
	size_t	len;
	bool	error;
	char	extra[];
}	t_lstring;

void		*ft_calloc(size_t count, size_t size);
bool		tr_a(void ***c, unsigned int k, int d, t_lstring *s);
t_lstring	*tr_p(void ***c, unsigned int k, int d);
size_t		lstrlen_until(t_lstring *self, char delimiter);
bool		lstrsplit(t_lstring *self, t_lstring **a, t_lstring **b, size_t i);

typedef void	***t_v3;

#endif
