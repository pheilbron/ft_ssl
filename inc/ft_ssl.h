/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 13:36:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 22:08:52 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_H
# define FT_SSL_H

# include <stdint.h>
# include "ft_ssl_error.h"
# include "ft_ssl_file.h"
# include "ft_queue.h"
# include "ft_error.h"
# include "ft_dstring.h"

# define LITTLE_END 1
# define LE 1
# define BIG_END 2
# define BE 2

# define READ_BUF_SIZE 4096

typedef uint16_t	t_flag;

typedef struct	s_ssl_algorithm_type
{
	t_flag	family : 2;
	t_flag	algo : 11;
	t_flag	mode : 3;
}				t_ssl_algorithm_type;

typedef struct	s_ssl_algorithm
{
	t_ssl_algorithm_type	type;
	char					*name;
	int						(*f)(void *, char **, uint16_t);
	void					(*process)();
}				t_ssl_algorithm;

typedef struct	s_ssl_context
{
	t_ssl_algorithm	algorithm;
	uint16_t		options;
	void			*data;
	t_error			e;
}				t_ssl_context;

extern t_ssl_algorithm	g_algo_tab[];

t_dstring		*get_ssl_options(t_dstring *s, t_ssl_algorithm_type type);
char			*get_ssl_command(t_ssl_algorithm_type type);
t_dstring		*get_ssl_commands(t_dstring *s, t_ssl_algorithm_type type);

int				parse_input(t_ssl_context *c, char **data, int len);
int				set_ssl_option(t_ssl_context *c, char op);
int				set_ssl_long_option(t_ssl_context *c, char *op);
int				parse_cipher(t_ssl_context *c, char **data, int len, int *i);
void			parse_standard(t_ssl_context *c, char **data, int len, int *i);
void			parse_message_digest(t_ssl_context *c, char **data, int len,
		int *i);

char			*nrandom(size_t n);

int				print_usage(t_ssl_context c);
int				print_fatal_error(t_ssl_context c);
void			print_non_fatal_error(t_ssl_file *file, char *algorithm_name);
void			set_ssl_error(t_ssl_file *file, char *algorithm_name,
		t_error e);
void			ft_ssl_error_init(t_error *e);
void			init_ssl_error(t_error *e);
int				ft_ssl_free_error(t_error *e);
int				ft_ssl_new_error(t_error *e, int no, char *data);

#endif
