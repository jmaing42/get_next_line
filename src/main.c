/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:52:18 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/20 00:13:11 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <dlfcn.h>

/*

static int	g_alloc = 0;

void	*malloc(size_t size)
{
	static void	*(*real)(size_t);
	void		*result;

	if (!real)
		real = dlsym(RTLD_NEXT, "malloc");
	result = real(size);
	fprintf(stderr, "malloc(%zd) called", size);
	if (!result)
		puts(" but failed");
	else
		printf(" (allocated %d chunks)\n", ++g_alloc);
	return (result);
}

void	free(void *ptr)
{
	static void	(*real)(void *);

	if (!real)
		real = dlsym(RTLD_NEXT, "free");
	if (ptr)
		fprintf(stderr, "free() called (allocated %d chunks)\n", --g_alloc);
	real(ptr);
}

//*/

int	main(void)
{
	char	*str;

	str = get_next_line(STDIN_FILENO);
	while (str)
	{
		printf("read:\t%s", str);
		free(str);
		str = get_next_line(STDIN_FILENO);
	}
	return (0);
}
