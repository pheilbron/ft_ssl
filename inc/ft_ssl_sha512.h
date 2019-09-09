/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:08:43 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 18:03:12 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA512_H
# define FT_SSL_SHA512_H

# include <stdint.h>

# define A 0
# define B 1
# define C 2
# define D 3
# define E 4
# define F 5
# define G 6
# define H 7

# define S0 0
# define S1 1

#define FIRST_LEN(x) (x / (ULLONG_MAX / 8))

typedef struct	s_sha512_chunk
{
	uint64_t	*data;
	uint64_t	len;
	uint64_t	pos;
	uint64_t	s[80];
	uint64_t	hash[8];
	uint64_t	temp[8];
}				t_sha512_chunk;

extern uint64_t	g_sha512_tab[];

void		ft_ssl_sha384(char *data, uint32_t **file_hash);
void		ft_ssl_sha512(char *data, uint32_t **file_hash);

uint64_t    sha512message_schedule_sum(uint64_t message_schedule[80], uint8_t offset,
        uint8_t type);
uint64_t    sha512compression_sum(t_sha512_chunk *c, uint8_t type);
uint64_t    sha512choice(t_sha512_chunk *c);
uint64_t    sha512majority(t_sha512_chunk *c);

#endif
