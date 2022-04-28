/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.h                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:36:47 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/28 09:08:06 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_BONUS_H
# define GET_NEXT_LINE_BONUS_H

# include <stddef.h>
# include <stdbool.h>

char		*get_next_line(int fd);

typedef struct s_lstring {
	size_t	len;
	bool	error;
	char	extra[];
}	t_lstring;

void		*ft_calloc(size_t count, size_t size);
bool		tr_a(void ***c, unsigned int k, int d, t_lstring *s);
t_lstring	*tr_p(void ***c, unsigned int k, int d);

typedef void	t_v;
typedef void	*t_v1;
typedef void	**t_v2;
typedef void	***t_v3;

#endif
