/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jmaing <jmaing@student.42seoul.kr>         +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/28 11:52:18 by jmaing            #+#    #+#             */
/*   Updated: 2022/04/28 13:27:23 by jmaing           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "get_next_line_bonus.h"

#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>

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
