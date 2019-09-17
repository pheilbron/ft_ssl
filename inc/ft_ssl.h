/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:36:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 14:31:46 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include "ft_ssl_error.h"
# include "ft_queue.h"
# include "ft_dstring.h"

# define LITTLE_ENDIAN 1
# define LE 1
# define BIG_ENDIAN 2
# define BE 2

typedef	union	u_ssl_algorithm_type
{
	uint16_t	reference;
	struct
	{
		uint16_t	family : 2;
		uint16_t	type : 14;
	}			algorithm;
}				t_ssl_algorithm_type;

typedef struct	s_ssl_file
{
	int			fd;
	char		*reference;
	uint8_t		print_flag;
	t_error		e;
}				t_ssl_file;

typedef struct	s_ssl_algorithm
{
	t_ssl_algorithm_type	type;
	char					*name;
	void					(*f)();
	void					(*process)();
	void					(*print)();
}				t_ssl_algorithm;

typedef struct	s_ssl_context
{
	t_ssl_algorithm	algorithm;
	uint16_t		options;
	t_queue			*data;
	t_error			e;
}				t_ssl_context;

extern t_ssl_algorithm	g_algo_tab[];

t_dstring		*get_ssl_options(t_dstring *s, t_ssl_algorithm_type type);
char			*get_ssl_command(t_ssl_algorithm_type type);
t_dstring		*get_ssl_commands(t_dstring *s, t_ssl_algorithm_type type);

int				parse_input(t_ssl_context *c, char **data, int len);
int				set_ssl_options(t_ssl_context *c, char op);
void			parse_cipher(t_ssl_context *c, char **data, int len, int *i);
void			parse_standard(t_ssl_context *c, char **data, int len, int *i);
void			parse_message_digest(t_ssl_context *c, char **data, int len,
		int *i);
int				print_usage(t_ssl_context c);
int				print_fatal_error(t_ssl_context c);
void			print_non_fatal_error(t_ssl_hash *hash);
void			set_ssl_error(t_ssl_file *file, char *algorithm_name,
		t_error e);
void			ft_ssl_error_init(t_error *e);
int				ft_ssl_free_error(t_error *e);

#endif
