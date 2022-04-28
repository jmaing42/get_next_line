/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_bonus.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:42:26 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/28 13:24:10 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include <unistd.h>
#include <stdlib.h>

static t_lstring	*read_lstring(int fd)
{
	t_lstring *const	result = malloc(sizeof(t_lstring) + BUFFER_SIZE);
	ssize_t				length;

	if (!result)
		return (NULL);
	length = read(fd, result->extra, BUFFER_SIZE);
	if (length < 0)
		return (free(result), NULL);
	result->len = length;
	return (result);
}

static t_lstring	*concat(t_lstring *a, t_lstring *b)
{
	t_lstring	*result;
	size_t		i;

	result = NULL;
	if (a && b)
		result = malloc(sizeof(t_lstring) + a->len + b->len);
	if (result)
	{
		result->len = a->len + b->len;
		i = -1;
		while (++i < a->len)
			result->extra[i] = a->extra[i];
		i--;
		while (++i < result->len)
			result->extra[i] = b->extra[i - a->len];
	}
	return (free(a), free(b), result);
}

static char	*lstrtocstr(const t_lstring *from)
{
	char *const	result = malloc(from->len + 1);
	size_t		i;

	i = -1;
	if (!result)
		return (NULL);
	while (++i < from->len)
		result[i] = from->extra[i];
	result[i] = '\0';
	return (result);
}

char	*get_next_line(int fd)
{
	static void	**map = NULL;
	t_lstring	*buffer;
	t_lstring	*current;

	current = tr_p(&map, *((unsigned int *)&fd), 0);
	while (!current || lstrlen_until(current, '\n') == current->len)
	{
		buffer = read_lstring(fd);
		if (buffer && buffer->len == 0 && current)
			return (free(buffer), lstrtocstr(current));
		if (buffer && buffer->len == 0)
			return (free(buffer), NULL);
		if (!current)
			current = buffer;
		else
			current = concat(current, buffer);
		if (!current)
			return (free(current), NULL);
	}
	if (lstrsplit(current, &current, &buffer, lstrlen_until(current, '\n') + 1))
		return (NULL);
	if (tr_a(&map, *((unsigned int *)&fd), 0, buffer))
		return (free(current), NULL);
	return (lstrtocstr(current));
}
