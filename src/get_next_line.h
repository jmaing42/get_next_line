/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:36:47 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/19 01:58:44 by Juyeong Maing    ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GET_NEXT_LINE_H
# define GET_NEXT_LINE_H

# include <stddef.h>
# include <stdbool.h>
# include <limits.h>

# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 4
# elif BUFFER_SIZE < 1
#  error "BUFFER_SIZE must be positive number"
# endif

char	*get_next_line(int fd);

typedef struct s_ft_get_line_buffer_list_node
{
	struct s_ft_get_line_buffer_list_node	*prev;
	struct s_ft_get_line_buffer_list_node	*next;
	size_t									length;
	char									extra[];
}	t_ft_get_line_buffer_list_node;

typedef struct s_ft_get_line_context
{
	t_ft_get_line_buffer_list_node	*head;
	t_ft_get_line_buffer_list_node	*tail;
	size_t							offset;
	size_t							length;
}	t_ft_get_line_context;

typedef union u_ft_get_line_trie_child
{
	struct s_ft_get_line_trie_node	*non_leaf;
	t_ft_get_line_context			*leaf;
}	t_ft_get_line_trie_child;

typedef struct s_ft_get_line_trie_node
{
	size_t						child_count;
	t_ft_get_line_trie_child	*child[1 << CHAR_BIT];
}	t_ft_get_line_trie_node;

typedef bool	t_err;

t_err	ft_get_line(
			char **out_line,
			size_t *out_line_length,
			t_ft_get_line_context *context);

t_err	ft_get_line_drain(
			char **out_line,
			size_t *out_line_length,
			bool *out_is_eof,
			t_ft_get_line_context *context);

t_err	ft_get_line_feed(
			char *buffer,
			size_t length,
			t_ft_get_line_context *context);

t_err	ft_get_line_trie_pop(
			t_ft_get_line_trie_child *root,
			int fd_key);

t_err	ft_get_line_trie_push(
			t_ft_get_line_trie_child *root,
			int fd_key);

#endif
