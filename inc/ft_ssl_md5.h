/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md5.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 18:54:01 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 13:43:56 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD5_H
# define FT_SSL_MD5_H

# include <stdint.h>
# include "ft_ssl_md_block.h"

#define A 0
#define B 1
#define C 2
#define D 3

typedef struct	s_md5_chunk
{
	t_u32_md_block	block;
	uint32_t		buf_len;
	uint32_t		buf_pos;
	uint32_t		hash[4];
	uint32_t		temp[4];
}				t_md5_chunk;

#endif
