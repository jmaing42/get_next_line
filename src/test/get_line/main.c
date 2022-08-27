/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/08/23 23:59:16 by Juyeong Maing     #+#    #+#             */
/*   Updated: 2022/08/28 01:32:07 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../../get_next_line.h"

#include <stdlib.h>
#include <unistd.h>
#include <fcntl.h>

static char	g_buffer[BUFFER_SIZE];

int	initial_fd(int argc, char **argv)
{
	if (argc < 2)
		return (STDIN_FILENO);
	return (open(argv[1], O_RDONLY));
}

int	main(int argc, char **argv)
{
	const int						fd = initial_fd(argc, argv);
	t_ft_get_line_context *const	context = ft_get_line_context(NULL, fd);
	char							*line;
	size_t							length;

	if (!context)
		return (EXIT_FAILURE);
	if (ft_get_line(&line, &length, g_buffer, context))
		return (EXIT_FAILURE);
	while (line)
	{
		write(STDOUT_FILENO, line, length);
		free(line);
		if (ft_get_line(&line, &length, g_buffer, context))
			return (EXIT_FAILURE);
	}
	ft_get_line_context(context, -1);
	return (EXIT_SUCCESS);
}
