/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fake_file_name (file name is useless too)          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: 42header-remover <whatever@example.com>    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 1970/01/01 00:00:00 by VCS handles       #+#    #+#             */
/*   Updated: 1970/01/01 00:00:00 by file history     ###   ########.fr       */
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

char					*get_next_line(int fd);

typedef struct s_ft_get_line_buffer_list_node
{
	struct s_ft_get_line_buffer_list_node	*next;
	size_t									length;
	size_t									capacity;
	char									*buffer;
	bool									has_nl;
}	t_ft_get_line_buffer_list_node;

typedef struct s_ft_get_line_context
{
	t_ft_get_line_buffer_list_node	*head;
	t_ft_get_line_buffer_list_node	*tail;
	int								fd;
	bool							eof;
}	t_ft_get_line_context;

typedef union u_ft_get_line_trie_child
{
	struct s_ft_get_line_trie_node	*non_leaf;
	t_ft_get_line_context			*leaf;
	void							*any;
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

typedef struct s_get_next_line_static
{
	t_ft_get_line_trie_node	*root;
	t_ft_get_line_context	*last_context;
	int						last_fd;
	char					buffer[BUFFER_SIZE];
}	t_get_next_line_static;

typedef bool	t_err;

void					*ft_get_line_internal_allocate(
							void *original,
							size_t size,
							size_t copy);

/**
 * @brief read buffer to get_line_context, get line from get_line_context
 *
 * @param out_line result, NULL on no more line
 * @param out_line_length length of result
 * @param context
 * @return true on failure
 * @return false on success
 */
t_err					ft_get_line(
							char **out_line,
							size_t *out_line_length,
							char *buffer,
							t_ft_get_line_context *context);

/**
 * @brief optionally free old, and optionally allocate new ft_get_line context
 *
 * @param old context free, if not NULL
 * @param fd fd of new context, if not negative
 * @return t_ft_get_line_context* NULL if fd is negative, new context otherwise
 */
t_ft_get_line_context	*ft_get_line_context(
							t_ft_get_line_context *old,
							int fd);

/**
 * @brief drain line from get_line_context
 *
 * @param out_line result, must be initialized to NULL before called
 * @param out_line_length length of result
 * @param return_complete_line bring NULL on incomplete line if false
 * @param context drain target
 * @remarks this is internal function for ft_get_line
 */
t_err					ft_get_line_drain(
							char **out_line,
							size_t *out_line_length,
							bool return_complete_line,
							t_ft_get_line_context *context);

/**
 * @brief feed buffer to get_line_context
 *
 * @param buffer buffer to feed (always consumed)
 * @param length buffer length to feed
 * @param context feed target
 * @return t_err true if failed
 * @remarks this is internal function for ft_get_line
 */
t_err					ft_get_line_feed(
							const char *buffer,
							size_t length,
							t_ft_get_line_context *context);

/**
 * @brief remove value associated with key, and get removed value
 *
 * @param out result
 * @param node address of trie node
 * @param key dictionary key
 * @param level for internal use, default 0
 * @return true if key exists
 * @return false if key not exists
 * @remarks *out is available only if true is returned
 */
bool					ft_get_line_trie_pop(
							t_ft_get_line_context **out,
							t_ft_get_line_trie_node **node,
							int key,
							int level);

t_err					ft_get_line_trie_push(
							t_ft_get_line_context *value,
							t_ft_get_line_trie_node **node,
							int key,
							int level);

#endif
