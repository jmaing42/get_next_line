/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:59:16 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/08/24 23:40:42 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <dlfcn.h>

static int	g_alloc = 0;

void	*malloc(size_t size)
{
	static void	*(*real)(size_t);
	void		*result;

	if (!real)
		real = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
	result = real(size);
	if (result)
		g_alloc++;
	return (result);
}

void	free(void *ptr)
{
	static void	(*real)(void *);

	if (!real)
		real = (void (*)(void *))dlsym(RTLD_NEXT, "free");
	if (ptr)
		g_alloc--;
	real(ptr);
}

static bool	test_pop(t_ft_get_line_trie_node **root)
{
	int						key;
	int						has_result;
	t_ft_get_line_context	*result;
	bool					test_result;

	scanf("%d %d", &key, &has_result);
	if (!!ft_get_line_trie_pop(&result, root, key, 0) != !!has_result)
		return (true);
	if (!has_result)
		return (false);
	scanf("%d", &key);
	test_result = result->fd != key;
	free(result);
	return (test_result);
}

static bool	test_push(t_ft_get_line_trie_node **root)
{
	int								key;
	t_ft_get_line_context *const	result
		= malloc(sizeof(t_ft_get_line_context));

	scanf("%d %d", &key, &result->fd);
	return (ft_get_line_trie_push(result, root, key, 0));
}

int	main(int argc, char **argv)
{
	t_ft_get_line_trie_node	*root;
	int						command;

	root = NULL;
	if (argc > 1 && !freopen(argv[1], "r", stdin))
		return (EXIT_FAILURE);
	while (scanf("%d", &command) == 1)
	{
		if (
			(command == 0 && test_pop(&root))
			|| (command == 1 && test_push(&root))
		)
			return (EXIT_FAILURE);
	}
	if (g_alloc)
		return (EXIT_FAILURE);
	return (EXIT_SUCCESS);
}
