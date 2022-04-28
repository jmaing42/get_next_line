/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:00:27 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/28 14:05:33 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <limits.h>

void	*ft_calloc(size_t count, size_t size)
{
	const size_t	length = size * count;
	void *const		result = malloc(length);
	size_t			i;

	if (!result)
		return (NULL);
	i = 0;
	while (i < length)
		((char *)result)[i++] = '\0';
	return (result);
}

bool	tr_a(void ***c, unsigned int k, int d, t_lstring *s)
{
	t_lstring	*tmp;
	size_t		i;

	if (c && !*c)
		*c = ft_calloc(1 << CHAR_BIT, sizeof(void *));
	if (!c || !*c)
		return (true);
	if (++d != sizeof(int))
		return (tr_a((t_v3)(&(*c)[k % (1 << CHAR_BIT)]), k >> CHAR_BIT, d, s));
	if (!s || !(*c)[k])
		return ((!s && (free((*c)[k]), true)) || (((*c)[k] = s), !s));
	tmp = malloc(sizeof(t_lstring) + ((t_lstring *)(*c)[k])->len + s->len);
	if (tmp && (*c)[k] && s)
	{
		tmp->len = ((t_lstring *)(*c)[k])->len + s->len;
		i = -1;
		while (++i < ((t_lstring *)(*c)[k])->len)
			tmp->extra[i] = ((t_lstring *)(*c)[k])->extra[i];
		i--;
		while (++i < ((t_lstring *)(*c)[k])->len + s->len)
			tmp->extra[i] = s->extra[i - ((t_lstring *)(*c)[k])->len];
	}
	else
		free(tmp);
	return (free((*c)[k]), free(s), !((*c)[k] = tmp));
}

t_lstring	*tr_p(void ***c, unsigned int k, int d)
{
	t_lstring	*result;
	size_t		i;
	bool		not_need_free;

	d++;
	if (c && d == sizeof(int))
	{
		result = (*c)[k];
		(*c)[k] = NULL;
	}
	else if (c && *c)
		result = tr_p((t_v3)(&(*c)[k % (1 << CHAR_BIT)]), k >> CHAR_BIT, d);
	else
		result = NULL;
	not_need_free = false;
	i = -1;
	while (++i < (1 << CHAR_BIT) && !not_need_free)
		not_need_free = (c && (*c) && !!(*c)[i]);
	if (!not_need_free)
		*c = (free(*c), NULL);
	return (result);
}

size_t	lstrlen_until(t_lstring *self, char delimiter)
{
	size_t	i;

	i = -1;
	while (++i < self->len)
		if (self->extra[i] == delimiter)
			break ;
	return (i);
}

bool	lstrsplit(t_lstring *self, t_lstring **o_a, t_lstring **o_b, size_t p)
{
	t_lstring *const	a = malloc(sizeof(t_lstring) + p);
	t_lstring *const	b = malloc(sizeof(t_lstring) + self->len - p);
	size_t				i;

	if (!a || !b)
		return (free(self), free(o_a), free(o_b), true);
	a->len = p;
	b->len = self->len - p;
	i = -1;
	while (++i < p)
		a->extra[i] = self->extra[i];
	i--;
	while (++i < self->len)
		b->extra[i - p] = self->extra[i];
	*o_a = a;
	*o_b = b;
	return (free(self), false);
}
