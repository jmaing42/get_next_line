/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:00:27 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/27 15:53:27 by Juyeong Maing    ###   ########.fr       */
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

t_ft_get_line_context	*ft_get_line_context(
	t_ft_get_line_context *old,
	int fd
)
{
	t_ft_get_line_buffer_list_node	*tmp;
	t_ft_get_line_context			*result;

	if (old)
	{
		while (old->head)
		{
			tmp = old->head;
			old->head = old->head->next;
			free(tmp->buffer);
			free(tmp);
		}
		free(old);
	}
	if (fd < 0)
		return (NULL);
	result = malloc(sizeof(t_ft_get_line_context));
	if (!result)
		return (NULL);
	result->head = NULL;
	result->tail = NULL;
	result->fd = fd;
	result->eof = false;
	return (result);
}

t_err	ft_get_line_drain(
	char **out_line,
	size_t *out_line_length,
	bool return_complete_line,
	t_ft_get_line_context *context
)
{
	t_ft_get_line_buffer_list_node	*tmp;

	if (context->head && (!return_complete_line || context->head->has_nl))
	{
		tmp = context->head;
		context->head = context->head->next;
		if (context->head == NULL)
			context->tail = NULL;
		*out_line = ft_get_line_internal_allocate(
				tmp->buffer, tmp->length + 1, tmp->length + 1);
		*out_line_length = tmp->length;
		free(tmp);
		return (!*out_line);
	}
	*out_line = NULL;
	return (false);
}
