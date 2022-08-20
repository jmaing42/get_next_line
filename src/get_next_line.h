/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_next_line.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: Juyeong Maing <jmaing@student.42seoul.kr>  +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2022/04/27 21:36:47 by jmaing            #+#    #+#             */
/*   Updated: 2022/08/20 20:03:51 by Juyeong Maing    ###   ########.fr       */
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
	int								fd;
	bool							eof;
}	t_ft_get_line_context;

typedef union u_ft_get_line_trie_child
{
	struct s_ft_get_line_trie_node	*non_leaf;
	t_ft_get_line_context			*leaf;
}	t_ft_get_line_trie_child;

typedef struct s_ft_get_line_trie_node
{
	size_t						child_count;
	t_ft_get_line_trie_child	child[1 << CHAR_BIT];
}	t_ft_get_line_trie_node;

typedef union u_ft_get_line_trie_key
{
	int				fd;
	unsigned char	index[sizeof(int)];
}	t_ft_get_line_trie_key;

typedef bool	t_err;

/**
 * @brief read buffer to get_line_context, get line from get_line_context
 *
 * @param out_line result, NULL on no more line
 * @param out_line_length length of result
 * @param context drain target
 * @return t_err true if failed
 */
t_err	ft_get_line(
			char **out_line,
			size_t *out_line_length,
			t_ft_get_line_context *context);

/**
 * @brief drain line from get_line_context
 *
 * @param out_line result
 * @param out_line_length length of result
 * @param return_complete_line bring NULL on incomplete line if false
 * @param context drain target
 * @return t_err true if failed
 */
t_err	ft_get_line_drain(
			char **out_line,
			size_t *out_line_length,
			bool return_complete_line,
			t_ft_get_line_context *context);

/**
 * @brief feed buffer to get_line_context, if ft_get_line_drain() got NULL
 *
 * @param buffer buffer to feed (always consumed)
 * @param length buffer length to feed
 * @param context feed target
 * @return t_err true if failed
 */
t_err	ft_get_line_feed(
			char *buffer,
			size_t length,
			t_ft_get_line_context *context);

void	ft_get_line_free(
			t_ft_get_line_context *context);

t_err	ft_get_line_trie_pop(
			t_ft_get_line_context **out,
			t_ft_get_line_trie_child **node,
			int key,
			int level);

t_err	ft_get_line_trie_push(
			t_ft_get_line_context *value,
			t_ft_get_line_trie_child **node,
			int key,
			int level);

#endif
