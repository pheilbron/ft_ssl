/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_message_digest.h                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:23:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 10:53:41 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MESSAGE_DIGEST_H
# define FT_SSL_MESSAGE_DIGEST_H

# include <stdint.h>
# include "ft_ssl.h"

# define MD_FILE 1
# define MD_BUFFER 2

# define ONLOAD 1
# define OFFLOAD 2

int		ft_ssl_md5(void *data, char **hash, uint16_t type);
int		ft_ssl_sha1(void *data, char **hash, uint16_t type);
int		ft_ssl_sha224(void *data, char **hash, uint16_t type);
int		ft_ssl_sha256(void *data, char **hash, uint16_t type);
int		ft_ssl_sha384(void *data, char **hash, uint16_t type);
int		ft_ssl_sha512(void *data, char **hash, uint16_t type);
int		ft_ssl_sha512_224(void *data, char **hash, uint16_t type);
int		ft_ssl_sha512_256(void *data, char **hash, uint16_t type);

void	process_message_digest(t_ssl_context *c);
void	ft_ssl_md_print(t_ssl_file *file, char *hash, t_ssl_context *c);
void	ft_ssl_print_md_error(t_ssl_file *file, char *algorithm_name);

#endif
