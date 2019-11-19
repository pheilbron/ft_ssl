/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_cipher.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 08:38:57 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/07 12:51:16 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_CIPHER_H
# define FT_SSL_CIPHER_H

# include <stdint.h>

# define DONE -1

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

int			ft_ssl_base64(void *data, char **out, uint16_t type);
int			ft_ssl_des_cbc(void *data, char **out, uint16_t type);
int			ft_ssl_des_cfb(void *data, char **out, uint16_t type);
int			ft_ssl_des_ctr(void *data, char **out, uint16_t type);
int			ft_ssl_des_ecb(void *data, char **out, uint16_t type);
int			ft_ssl_des_ofb(void *data, char **out, uint16_t type);
int			ft_ssl_des_pcbc(void *data, char **out, uint16_t type);

uint64_t	ft_ssl_des_pbkdf(char *password);
int			set_u64_block(uint64_t *out, int fd,
		void (*pad)(char *, char *, int, int));

void		process_cipher(t_ssl_context *c);

#endif
