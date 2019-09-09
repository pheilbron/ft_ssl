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

# define S0 0
# define S1 1

typedef struct	s_sha256_chunk
{
	uint32_t	*data;
	uint32_t	len;
	uint32_t	pos;
	uint32_t	s[64];
	uint32_t	hash[8];
	uint32_t	temp[8];
}				t_sha256_chunk;

extern uint32_t	g_sha256_tab[];

void		ft_ssl_sha224(char *data, uint32_t **file_hash);
void		ft_ssl_sha256(char *data, uint32_t **file_hash);

uint32_t    message_schedule_sum(uint32_t message_schedule[64], uint8_t offset,
        uint8_t type);
uint32_t    compression_sum(t_sha256_chunk *c, uint8_t type);
uint32_t    choice(t_sha256_chunk *c);
uint32_t    majority(t_sha256_chunk *c);

#endif
