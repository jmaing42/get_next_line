/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:00:27 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/20 00:06:52 by Juyeong Maing    ###   ########.fr       */
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
	t_ft_get_line_trie_child **node,
	int key,
	int level
)
{
	const t_ft_get_line_trie_key	k = {.fd = key};
	bool							result;

	if (level == sizeof(int))
	{
		*out = (*node)->leaf;
		(*node)->leaf = NULL;
		return (false);
	}
	if (!(*node)->non_leaf->child[k.index[level]])
	{
		*out = NULL;
		return (false);
	}
	result = ft_get_line_trie_pop(
			out, &(*node)->non_leaf->child[k.index[level]], key, level + 1);
	if (!(*node)->non_leaf->child[k.index[level]]
		&& !--(*node)->non_leaf->child_count)
	{
		free(*node);
		*node = NULL;
	}
	return (result);
}

t_err	ft_get_line_trie_push(
	t_ft_get_line_context *value,
	t_ft_get_line_trie_child **node,
	int key,
	int level
)
{
	const t_ft_get_line_trie_key	k = {.fd = key};
	bool							result;
	bool							had_child;

	if (level == sizeof(int))
		(*node)->leaf = value;
	if (level == sizeof(int))
		return (false);
	had_child = !!(*node)->non_leaf->child[k.index[level]];
	if (!had_child)
		(*node)->non_leaf->child[k.index[level]]
			= ft_calloc(1, sizeof(t_ft_get_line_trie_child));
	if (!(*node)->non_leaf->child[k.index[level]])
		return (true);
	result = ft_get_line_trie_push(
			value, &(*node)->non_leaf->child[k.index[level]], key, level + 1);
	if (!had_child && (*node)->non_leaf->child[k.index[level]])
		(*node)->non_leaf->child_count++;
	if (!(*node)->non_leaf->child_count)
	{
		free(*node);
		*node = NULL;
	}
	return (result);
}
