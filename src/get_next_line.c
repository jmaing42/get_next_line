/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 10:42:26 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/27 10:13:16 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>
#include <unistd.h>

char	*get_next_line(int fd)
{
	static t_ft_get_line_trie_node	*node = NULL;
	char							*result;
	size_t							unused_result_length;
	t_ft_get_line_context			*context;

	if (!ft_get_line_trie_pop(&context, &node, fd, 0))
		context = ft_get_line_context(NULL, fd);
	if (!context)
		return (NULL);
	if (ft_get_line(&result, &unused_result_length, context))
	{
		ft_get_line_context(context, -1);
		return (NULL);
	}
	if (!result || ft_get_line_trie_push(context, &node, fd, 0))
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

t_err	ft_get_line_feed(
	char *buffer,
	size_t length,
	t_ft_get_line_context *context
)
{
	// TODO: implement
	return (false);
}
