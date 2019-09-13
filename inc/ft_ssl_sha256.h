/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:02:15 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 18:03:14 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA256_H
# define FT_SSL_SHA256_H

# include <stdint.h>

# define A 0
# define B 1
# define C 2
# define D 3
# define E 4
# define F 5
# define G 6
# define H 7

typedef struct	s_sha256_chunk
{
	t_u32_md_block	block;
	uint32_t	s[64];
	uint32_t	hash[8];
	uint32_t	temp[8];
}				t_sha256_chunk;

extern uint32_t	g_sha256_tab[];

void			init_sha256_message_schedule(t_sha256_chunk *chunk)
void			compress_sha256_chunk(t_sha256_chunk *chunk)
void			update_sha256_message_schedule(t_sha256_chunk *chunk,
		uint8_t type)

#endif
