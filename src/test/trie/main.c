/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:59:16 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/08/24 23:05:32 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

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
	return (EXIT_SUCCESS);
}
