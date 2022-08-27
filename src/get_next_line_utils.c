/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:00:27 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/27 09:57:45 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdlib.h>

void	*ft_get_line_internal_allocate(
	void *original,
	size_t size,
	size_t copy
)
{
	void *const	result = malloc(size);
	size_t		i;

	if (result)
	{
		i = -1;
		if (original)
			while (++i < copy)
				((unsigned char *)result)[i] = ((unsigned char *)original)[i];
		else
			while (++i < copy)
				((unsigned char *)result)[i] = 0;
	}
	free(original);
	return (result);
}

bool	ft_get_line_trie_pop(
	t_ft_get_line_context **out,
	t_ft_get_line_trie_node **node,
	int key,
	int level
)
{
	const t_ft_get_line_trie_key	k = {.fd = key};
	bool							result;

	if (!*node || !(*node)->child[k.index[level]].any)
		return (false);
	if (level == sizeof(int) - 1)
	{
		*out = (*node)->child[k.index[level]].leaf;
		(*node)->child[k.index[level]].leaf = NULL;
		if (--(*node)->child_count)
			return (true);
		free(*node);
		*node = NULL;
		return (true);
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
		*node = ft_get_line_internal_allocate(NULL,
				sizeof(t_ft_get_line_trie_node),
				sizeof(t_ft_get_line_trie_node));
	if (!*node)
		return (true);
	if (level == sizeof(int) - 1)
	{
		(*node)->child[k.index[level]].leaf = value;
		(*node)->child_count++;
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
	size_t							i;

	context->length -= length;
	result[length] = '\0';
	i = 0;
	while (i < length)
	{
		result[i] = context->head->buffer[context->offset + i];
		if (context->offset + ++i == context->head->length)
		{
			length -= i;
			result += i;
			i = 0;
			tmp = context->head;
			context->head = context->head->next;
			context->offset = 0;
			if (!context->head)
				context->tail = NULL;
			free(tmp->buffer);
			free(tmp);
		}
	}
	context->offset = i;
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
