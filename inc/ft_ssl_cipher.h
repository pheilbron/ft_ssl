/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_cipher.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 08:38:57 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 21:07:06 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_CIPHER_H
# define FT_SSL_CIPHER_H

# include <stdint.h>
# include "ft_ssl.h"

# define DONE -1

# define IN_FILE 1
# define OUT_FILE 2

typedef struct	s_cipher_context
{
	t_ssl_file	*in_file;
	t_ssl_file	*out_file;
	char		*salt;
	char		*init_vect;
	char		*key[3];
	char		password[256];
	uint16_t	flag;
	t_error		e;
}				t_cipher_context;

int					ft_ssl_base64(void *data, char **out, uint16_t type);
int					ft_ssl_des(void *data, char **out, uint16_t type);
int					ft_ssl_des3(void *data, char **out, uint16_t type);

int					ft_ssl_des_pbkdf(char *password, char *salt,
		uint64_t (*key)[3], uint64_t *iv);
int					ft_ssl_des3_pbkdf(char *password, char *salt,
		uint64_t (*key)[3], uint64_t *iv);
int					set_u64_block(uint64_t *out, int fd,
		void (*pad)(char *, char *, int, int));

void				process_cipher(t_ssl_context *c);

int					clean_cipher_context(t_cipher_context *c);
t_cipher_context	*init_cipher_context(void);

#endif
