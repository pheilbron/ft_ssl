/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_cipher.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 08:38:57 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/23 17:07:37 by pheilbro         ###   ########.fr       */
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
}				t_cipher_context;

int			ft_ssl_base64(t_ssl_file *file, char *out);
int			ft_ssl_des_cbc(t_ssl_context *c, char *out);
int			ft_ssl_des_cfb(t_ssl_context *c, char *out);
int			ft_ssl_des_ctr(t_ssl_context *c, char *out);
int			ft_ssl_des_ecb(t_ssl_context *c, char *out);
int			ft_ssl_des_ofb(t_ssl_context *c, char *out);
int			ft_ssl_des_pcbc(t_ssl_context *c, char *out);

uint64_t	ft_ssl_des_pbkdf(char *password);
int			set_u64_block(uint64_t *out, int fd,
		void (*pad)(char *, char *, int, int));

int			process_cipher(t_ssl_context *c);

#endif
