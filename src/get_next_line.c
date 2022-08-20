/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:42:26 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/20 20:08:01 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>

static t_ft_get_line_context	*init_context(
	int fd,
	s_ft_get_line_trie_node *root
)
{
	t_ft_get_line_context	context;

	if (!ft_get_line_trie_pop(&context, root, fd, 0))
		return (context);
	context = malloc(sizeof(t_ft_get_line_context));
	if (!context)
		return (NULL);
	context->head = NULL;
	context->tail = NULL;
	context->offset = 0;
	context->length = 0;
	context->fd = fd;
	context->eof = false;
	return (context);
}

char	*get_next_line(int fd)
{
	static s_ft_get_line_trie_node	*node = NULL;
	char							*result;
	size_t							unused_result_length;
	t_ft_get_line_context *const	context = init_context(fd, &node);

	if (!context)
		return (NULL);
	if (ft_get_line(&result, &unused_result_length, context))
	{
		ft_get_line_free(context);
		return (true);
	}
	if (!result)
		ft_get_line_free(context);
	else if (ft_get_line_trie_push(context, &root, fd, 0))
		return (true);
	return (result);
}

t_err	ft_get_line(
	char **out_line,
	size_t *out_line_length,
	t_ft_get_line_context *context
)
{
	char	*buffer;
	ssize_t	bytes_read;

	*out_line = NULL;
	if (ft_get_line_drain(out_line, out_line_length, !context->eof, context))
		return (true);
	while (!*out_line)
	{
		buffer = malloc(BUFFER_SIZE);
		if (!buffer)
			return (true);
		bytes_read = read(context->fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
		{
			free(buffer);
			return (true);
		}
		else if (bytes_read == 0)
			context->eof = true;
		if (ft_get_line_feed(buffer, length, context)
			|| ft_get_line_drain(
				out_line, out_line_length, !context->eof, context))
			return (true);
	}
	return (false);
}

t_err	ft_get_line_drain(
	char **out_line,
	size_t *out_line_length,
	bool *out_is_eof,
	t_ft_get_line_context *context
)
{
	//
}

t_err	ft_get_line_feed(
	char *buffer,
	size_t length,
	t_ft_get_line_context *context
)
{
	//
}
