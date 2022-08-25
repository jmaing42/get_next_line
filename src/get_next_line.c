/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:42:26 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/25 21:27:36 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>

t_ft_get_line_context	*ft_get_line_init_context(int fd)
{
	t_ft_get_line_context *const	result
		= malloc(sizeof(t_ft_get_line_context));

	if (!result)
		return (NULL);
	result->head = NULL;
	result->tail = NULL;
	result->offset = 0;
	result->length = 0;
	result->fd = fd;
	result->eof = false;
	return (result);
}

char	*get_next_line(int fd)
{
	static t_ft_get_line_trie_node	*node = NULL;
	char							*result;
	size_t							unused_result_length;
	t_ft_get_line_context			*context;

	if (!ft_get_line_trie_pop(&context, &node, fd, 0))
		context = ft_get_line_init_context(fd);
	if (!context)
		return (NULL);
	if (ft_get_line(&result, &unused_result_length, context))
	{
		ft_get_line_free(context);
		return (NULL);
	}
	if (!result || ft_get_line_trie_push(context, &node, fd, 0))
	{
		ft_get_line_free(context);
		free(result);
		return (NULL);
	}
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
	while (!*out_line && !context->eof)
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
		if (ft_get_line_feed(buffer, bytes_read, context)
			|| ft_get_line_drain(
				out_line, out_line_length, !context->eof, context))
			return (true);
	}
	return (false);
}

t_err	ft_get_line_drain(
	char **out_line,
	size_t *out_line_length,
	bool return_complete_line,
	t_ft_get_line_context *context
)
{
	size_t	i;

	*out_line = NULL;
	if (!context->tail)
		return (false);
	i = -1;
	if (context->tail == context->head)
		i = context->offset - 1;
	while (++i < context->tail->length)
		if (context->tail->buffer[i] == '\n')
			break ;
	if (return_complete_line && i == context->tail->length)
		return (false);
	if (return_complete_line && i != context->tail->length)
		i++;
	*out_line_length = context->length - context->tail->length + i;
	if (!*out_line_length)
		return (false);
	*out_line = malloc(*out_line_length + 1);
	if (!*out_line)
		return (true);
	ft_get_line_drain_fill(*out_line, *out_line_length, context);
	return (false);
}

t_err	ft_get_line_feed(
	char *buffer,
	size_t length,
	t_ft_get_line_context *context
)
{
	t_ft_get_line_buffer_list_node *const	tail
		= malloc(sizeof(t_ft_get_line_buffer_list_node));

	if (!tail)
	{
		free(buffer);
		return (true);
	}
	context->length += length;
	tail->buffer = buffer;
	tail->length = length;
	tail->prev = context->tail;
	tail->next = NULL;
	if (context->tail)
		context->tail->next = tail;
	else
		context->head = tail;
	context->tail = tail;
	return (false);
}
