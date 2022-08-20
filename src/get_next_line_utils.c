/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:00:27 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/21 00:25:16 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>

static inline void	*ft_calloc(size_t count, size_t size)
{
	const size_t	length = size * count;
	void *const		result = malloc(length);
	size_t			i;

	if (!result)
		return (NULL);
	i = 0;
	while (i < length)
		((unsigned char *)result)[i++] = 0;
	return (result);
}

t_err	ft_get_line_trie_pop(
	t_ft_get_line_context **out,
	t_ft_get_line_trie_node **node,
	int key,
	int level
)
{
	const t_ft_get_line_trie_key	k = {.fd = key};
	bool							result;

	*out = NULL;
	if (!*node)
		return (false);
	if (level == sizeof(int) - 1)
	{
		*out = (*node)->child[k.index[level]].leaf;
		(*node)->child[k.index[level]].leaf = NULL;
		if (--(*node)->child_count)
			return (false);
		free(*node);
		*node = NULL;
		return (false);
	}
	result = ft_get_line_trie_pop(
			out, &(*node)->child[k.index[level]].non_leaf, key, level + 1);
	if ((*node)->child[k.index[level]].non_leaf || --(*node)->child_count)
		return (result);
	free(*node);
	*node = NULL;
	return (result);
}

t_err	ft_get_line_trie_push(
	t_ft_get_line_context *value,
	t_ft_get_line_trie_node **node,
	int key,
	int level
)
{
	const t_ft_get_line_trie_key	k = {.fd = key};
	bool							result;

	if (!*node)
		*node = ft_calloc(1, sizeof(t_ft_get_line_trie_node));
	if (!*node)
		return (true);
	if (level == sizeof(int) - 1)
	{
		(*node)->child[k.index[level]].leaf = value;
		return (false);
	}
	result = ft_get_line_trie_push(
			value, &(*node)->child[k.index[level]].non_leaf, key, level + 1);
	if ((*node)->child[k.index[level]].non_leaf)
		(*node)->child_count++;
	if (!(*node)->child_count)
	{
		free(*node);
		*node = NULL;
	}
	return (result);
}

void	ft_get_line_drain_fill(
	char *result,
	size_t length,
	t_ft_get_line_context *context
)
{
	t_ft_get_line_buffer_list_node	*tmp;
	size_t							current_index;
	size_t							i;

	current_index = context->offset;
	i = -1;
	while (++i < length)
	{
		result[i] = context->head->buffer[context->offset + current_index];
		if (context->offset + ++current_index == context->head->length)
		{
			tmp = context->head;
			if (!context->head->next)
				context->tail = NULL;
			length -= i;
			result += i;
			i = 0;
			context->head = context->head->next;
			context->offset = 0;
			free(tmp->buffer);
			free(tmp);
		}
	}
	context->offset = current_index;
}

void	ft_get_line_free(
	t_ft_get_line_context *context
)
{
	t_ft_get_line_buffer_list_node	*tmp;

	while (context->head)
	{
		tmp = context->head;
		context->head = context->head->next;
		free(tmp->buffer);
		free(tmp);
	}
	free(context);
}
