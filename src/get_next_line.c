/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:42:26 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/27 15:46:48 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static t_get_next_line_static	gnl;
	char							*result;
	size_t							unused_result_length;
	t_ft_get_line_context			*context;

	if (!ft_get_line_trie_pop(&context, &gnl.root, fd, 0))
		context = ft_get_line_context(NULL, fd);
	if (!context)
		return (NULL);
	if (ft_get_line(&result, &unused_result_length, gnl.buffer, context))
	{
		ft_get_line_context(context, -1);
		return (NULL);
	}
	if (!result || ft_get_line_trie_push(context, &gnl.root, fd, 0))
	{
		ft_get_line_context(context, -1);
		free(result);
		return (NULL);
	}
	return (result);
}

t_err	ft_get_line(
	char **out_line,
	size_t *out_line_length,
	char *buffer,
	t_ft_get_line_context *context
)
{
	ssize_t	bytes_read;

	*out_line = NULL;
	ft_get_line_drain(out_line, out_line_length, !context->eof, context);
	while (!*out_line && !context->eof)
	{
		bytes_read = read(context->fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (true);
		else if (bytes_read == 0)
			context->eof = true;
		if (ft_get_line_feed(buffer, bytes_read, context))
			return (true);
		ft_get_line_drain(out_line, out_line_length, !context->eof, context);
	}
	return (false);
}

static t_err	ft_get_line_feed_line_new(
	const char *buffer,
	size_t length,
	t_ft_get_line_context *context
)
{
	t_ft_get_line_buffer_list_node	*tmp;
	size_t							i;

	tmp = malloc(sizeof(t_ft_get_line_buffer_list_node));
	if (!tmp)
		return (true);
	tmp->buffer = malloc(length + 1);
	if (!tmp->buffer)
	{
		free(tmp);
		return (true);
	}
	tmp->capacity = length;
	tmp->length = length;
	tmp->has_nl = buffer[length - 1] == '\n';
	tmp->next = NULL;
	i = -1;
	while (++i < length)
		tmp->buffer[i] = buffer[i];
	tmp->buffer[length] = '\0';
	if (context->tail)
		context->tail->next = tmp;
	else
		context->head = tmp;
	context->tail = tmp;
	return (false);
}

static t_err	ft_get_line_feed_line(
	const char *buffer,
	size_t length,
	t_ft_get_line_context *context
)
{
	size_t	new_capacity;
	size_t	i;

	if (!context->tail || context->tail->has_nl)
		return (ft_get_line_feed_line_new(buffer, length, context));
	if (context->tail->length + length > context->tail->capacity)
	{
		new_capacity = context->tail->length + length;
		if (new_capacity < context->tail->capacity * 2)
			new_capacity = context->tail->capacity * 2;
		context->tail->buffer = ft_get_line_internal_allocate(
				context->tail->buffer, new_capacity + 1, context->tail->length);
		if (!context->tail->buffer)
			return (true);
		context->tail->capacity = new_capacity;
	}
	i = -1;
	while (++i < length)
		context->tail->buffer[context->tail->length + i] = buffer[i];
	context->tail->buffer[context->tail->length + i] = '\0';
	context->tail->length += length;
	context->tail->has_nl
		= context->tail->buffer[context->tail->length - 1] == '\n';
	return (false);
}

t_err	ft_get_line_feed(
	const char *buffer,
	size_t length,
	t_ft_get_line_context *context
)
{
	size_t	i;
	size_t	offset;

	offset = 0;
	i = -1;
	while (++i < length)
	{
		if (buffer[i] == '\n')
		{
			if (ft_get_line_feed_line(&buffer[offset], i + 1 - offset, context))
				return (true);
			offset = i + 1;
		}
	}
	if (
		offset != length
		&& ft_get_line_feed_line(&buffer[offset], length - offset, context)
	)
		return (true);
	return (false);
}
