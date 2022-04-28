/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   test.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 08:34:19 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/28 10:23:00 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "test.h"

#include <dlfcn.h>
#include <stdio.h>
#include <string.h>

#include "get_next_line_bonus.h"

static int	g_alloc_count = 0;

void	*malloc(size_t size)
{
	static void	*(*real)(size_t);
	void		*result;

	if (!real)
		real = dlsym(RTLD_NEXT, "malloc");
	result = real(size);
	printf("malloc(%zd) called", size);
	if (!result)
		puts(" but failed");
	else
		printf(" (allocated %d chunks)\n", ++g_alloc_count);
	return (result);
}

void	free(void *ptr)
{
	static void	(*real)(void *);

	if (!real)
		real = dlsym(RTLD_NEXT, "free");
	if (ptr)
		printf("free() called (allocated %d chunks)\n", --g_alloc_count);
	return (real(ptr));
}

t_lstring	*new_lstring(const char *str)
{
	t_lstring *const	result = malloc(sizeof(t_lstring) + strlen(str));

	if (!result)
		return (NULL);
	result->len = strlen(str);
	memcpy(result->extra, str, strlen(str));
	return (result);
}

int	main(void)
{
	void	**map;

	map = NULL;
	tr_a(&map, 42, 0, new_lstring("Hello"));
	tr_a(&map, 42, 0, new_lstring(" wor"));
	tr_a(&map, 42, 0, new_lstring("ld!"));
	tr_a(&map, 0x42, 0, new_lstring("test"));
	tr_a(&map, 4242, 0, new_lstring("test"));
	free(tr_p(&map, 42, 0));
	free(tr_p(&map, 4242, 0));
	free(tr_p(&map, 0x42, 0));
}
