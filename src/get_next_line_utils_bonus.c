/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils_bonus.c                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:00:27 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/28 09:09:48 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

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

	d++;
	if (c && !*c)
		*c = ft_calloc(1 << CHAR_BIT, sizeof(void *));
	if (!c || !*c)
		return (true);
	if (d != sizeof(int))
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
	bool		need_free;

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
	need_free = false;
	i = -1;
	while (++i < (1 << CHAR_BIT) && !need_free)
		need_free = (c && (*c) && !!(*c)[i]);
	if (need_free)
		*c = (free(*c), NULL);
	return (result);
}
