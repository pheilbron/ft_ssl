/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_message_digest.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:23:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 13:59:58 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MESSAGE_DIGEST_H
# define FT_SSL_MESSAGE_DIGEST_H

# include <stdint.h>
# include "ft_ssl.h"

void	ft_ssl_md5_buffer(char *in, char **hash);
void	ft_ssl_md5_file(t_ssl_file *file, char **hash);
void	ft_ssl_sha1_buffer(char *data, char **hash);
void	ft_ssl_sha1_file(t_ssl_file *file, char **hash);
void	ft_ssl_sha224_buffer(char *data, char **hash);
void	ft_ssl_sha224_file(t_ssl_file *file, char **hash);
void	ft_ssl_sha256_buffer(char *data, char **hash);
void	ft_ssl_sha256_file(t_ssl_file *file, char **hash);
void	ft_ssl_sha384_buffer(char *data, char **hash);
void	ft_ssl_sha384_file(t_ssl_file *file, char **hash);
void	ft_ssl_sha512_buffer(char *data, char **hash);
void	ft_ssl_sha512_file(t_ssl_file *file, char **hash);
void	ft_ssl_sha512_224_buffer(char *data, char **hash);
void	ft_ssl_sha512_224_file(t_ssl_file *file, char **hash);
void	ft_ssl_sha512_256_buffer(char *data, char **hash);
void	ft_ssl_sha512_256_file(t_ssl_file *file, char **hash);

void	ft_ssl_md_print(char *algo_name, uint8_t algo_ops, uint8_t hash_len,
		t_ssl_file *file);

#endif
