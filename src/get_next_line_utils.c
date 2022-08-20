/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line_utils.c                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 03:00:27 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/20 20:19:07 by Juyeong Maing    ###   ########.fr       */
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
	t_ft_get_line_trie_child **node,
	int key,
	int level
)
{
	const t_ft_get_line_trie_key	k = {.fd = key};
	bool							result;
	bool							had_child;

	if (!*node)
		*node = ft_calloc(1, sizeof(t_ft_get_line_trie_child));
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
