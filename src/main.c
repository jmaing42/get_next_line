/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:52:18 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/28 01:23:22 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>
#include <dlfcn.h>

// /*

static inline void	ft_putnbr(int fd, size_t n)
{
	const char	c = '0' + n % 10;

	if (n / 10)
		ft_putnbr(fd, n / 10);
	write(fd, &c, 1);
}

static int	g_alloc = 0;

void	*malloc(size_t size)
{
	static void	*(*real)(size_t);
	void		*result;

	if (!real)
		real = (void *(*)(size_t))dlsym(RTLD_NEXT, "malloc");
	result = real(size);
	write(STDERR_FILENO, "malloc called(", 14);
	ft_putnbr(STDERR_FILENO, size);
	if (!result)
		write(STDERR_FILENO, ") but failed\n", 13);
	else
	{
		write(STDERR_FILENO, ", allocated ", 12);
		ft_putnbr(STDERR_FILENO, ++g_alloc);
		write(STDERR_FILENO, " chunks)\n ", 9);
	}
	return (result);
}

void	free(void *ptr)
{
	static void	(*real)(void *);

	if (!real)
		real = (void (*)(void *))dlsym(RTLD_NEXT, "free");
	if (ptr)
	{
		write(STDERR_FILENO, "free() called (allocated ", 25);
		ft_putnbr(STDERR_FILENO, --g_alloc);
		write(STDERR_FILENO, " chunks)\n ", 9);
	}
	real(ptr);
}

//*/

int	main(int argc, char **argv)
{
	char	*str;
	int		fd;

	fd = STDIN_FILENO;
	if (argc > 1)
		fd = open(argv[1], O_RDONLY);
	str = get_next_line(fd);
	while (str)
	{
		write(STDOUT_FILENO, "read:\t", 6);
		write(STDOUT_FILENO, str, strlen(str));
		free(str);
		str = get_next_line(fd);
	}
	return (0);
}
