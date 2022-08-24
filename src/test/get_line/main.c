/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:59:16 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/08/25 00:38:47 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <fcntl.h>

int	initial_fd(int argc, char **argv)
{
	if (argc < 2)
		return (STDIN_FILENO);
	return (open(argv[1], O_RDONLY));
}

int	main(int argc, char **argv)
{
	const int						fd = initial_fd(argc, argv);
	t_ft_get_line_context *const	context = ft_get_line_init_context(fd);
	char							*str;
	size_t							unused_line_length;

	if (!context)
		return (EXIT_FAILURE);
	if (ft_get_line(&str, &unused_line_length, context))
		return (EXIT_FAILURE);
	while (str)
	{
		write(STDOUT_FILENO, str, strlen(str));
		free(str);
		if (ft_get_line(&str, &unused_line_length, context))
			return (EXIT_FAILURE);
	}
	return (EXIT_SUCCESS);
}
