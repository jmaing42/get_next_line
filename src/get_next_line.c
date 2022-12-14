/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_file_name (file name is useless too)          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42header-remover <whatever@example.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by file history     ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static t_get_next_line_static	gnl;
	char							*result;
	t_ft_get_line_context			*context;
	const bool						reusing
		= gnl.last_context && gnl.last_fd == fd;

	if (reusing)
		context = gnl.last_context;
	else if (!ft_get_line_trie_pop(&context, &gnl.root, fd, 0))
		context = ft_get_line_context(NULL, fd);
	if (!context)
		return (NULL);
	gnl.last_fd = fd;
	gnl.last_context = context;
	if (ft_get_line(&result, NULL, gnl.buffer, context) || !result
		|| (!reusing && ft_get_line_trie_push(context, &gnl.root, fd, 0)))
	{
		gnl.last_context = NULL;
		ft_get_line_trie_pop(&context, &gnl.root, fd, 0);
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
	size_t	line_length;

	*out_line = NULL;
	if (ft_get_line_drain(out_line, &line_length, !context->eof, context))
		return (true);
	while (!*out_line && !context->eof)
	{
		bytes_read = read(context->fd, buffer, BUFFER_SIZE);
		if (bytes_read < 0)
			return (true);
		else if (bytes_read == 0)
			context->eof = true;
		if (
			ft_get_line_feed(buffer, bytes_read, context)
			|| ft_get_line_drain(
				out_line, &line_length, !context->eof, context)
		)
			return (true);
	}
	if (out_line_length)
		*out_line_length = line_length;
	return (false);
}

static t_err	ft_get_line_feed_line_new(
	const char *buffer,
	size_t length,
	t_ft_get_line_context *context
)
{
	t_ft_get_line_buffer_list_node *const	tmp
		= malloc(sizeof(t_ft_get_line_buffer_list_node));
	char *const								tmp_buffer = malloc(length + 1);

	if (!tmp || !tmp_buffer)
	{
		free(tmp);
		free(tmp_buffer);
		return (true);
	}
	tmp->buffer = tmp_buffer;
	tmp->capacity = length;
	tmp->length = length;
	tmp->has_nl = buffer[length - 1] == '\n';
	tmp->next = NULL;
	tmp->buffer[length] = '\0';
	while (length--)
		tmp->buffer[length] = buffer[length];
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
