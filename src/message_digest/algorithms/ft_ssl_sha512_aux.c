/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:30:24 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 14:21:48 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha512.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_sha_utils.h"

static uint64_t	message_schedule_sum(uint64_t message_schedule[80],
		uint8_t offset, uint8_t type)
{
	if (type == S0)
		return (rot_r(message_schedule[offset - 2], 19, 64) ^
				rot_r(message_schedule[offset - 2], 61, 64) ^
				(message_schedule[offset - 2] >> 6));
	else if (type == S1)
		return (rot_r(message_schedule[offset - 15], 1, 64) ^
				rot_r(message_schedule[offset - 15], 8, 64) ^
				(message_schedule[offset - 15] >> 7));
	else
		return (0);
}

static uint64_t	compression_sum(t_sha512_chunk *c, uint8_t type)
{
	if (type == S0)
		return (rot_r(c->temp[A], 28, 64) ^ rot_r(c->temp[A], 34, 64) ^
				rot_r(c->temp[A], 39, 64));
	else if (type == S1)
		return (rot_r(c->temp[E], 14, 64) ^ rot_r(c->temp[E], 18, 64) ^
				rot_r(c->temp[E], 41, 64));
	else
		return (0);
}

void			init_sha512_message_schedule(t_sha512_chunk *chunk)
{
	uint8_t	i;

	i = 0;
	while (i < 16)
	{
		chunk->s[i] = chunk->block.data[chunk->buf_pos + i];
		i++;
	}
	while (i < 80)
	{
		chunk->s[i] = message_schedule_sum(chunk->s, i, S1) +
			chunk->s[i - 7] + message_schedule_sum(chunk->s, i, S0) +
			chunk->s[i - 16];
		i++;
	}
}

void			compress_sha512_chunk(t_sha512_chunk *chunk)
{
	uint8_t		i;
	uint64_t	temp1;
	uint64_t	temp2;

	i = 0;
	while (i < 80)
	{
		temp1 = compression_sum(chunk, S1) +
			u64_ch(chunk->temp[E], chunk->temp[F], chunk->temp[G]) +
			chunk->temp[H] + chunk->s[i] + g_sha512_tab[i];
		temp2 = compression_sum(chunk, S0) +
			u64_maj(chunk->temp[A], chunk->temp[B], chunk->temp[C]);
		chunk->temp[H] = chunk->temp[G];
		chunk->temp[G] = chunk->temp[F];
		chunk->temp[F] = chunk->temp[E];
		chunk->temp[E] = chunk->temp[D] + temp1;
		chunk->temp[D] = chunk->temp[C];
		chunk->temp[C] = chunk->temp[B];
		chunk->temp[B] = chunk->temp[A];
		chunk->temp[A] = temp1 + temp2;
		i++;
	}
}

void			update_sha512_message_schedule(t_sha512_chunk *chunk,
		uint8_t type)
{
	if (type == ONLOAD)
	{
		chunk->temp[A] = chunk->hash[A];
		chunk->temp[B] = chunk->hash[B];
		chunk->temp[C] = chunk->hash[C];
		chunk->temp[D] = chunk->hash[D];
		chunk->temp[E] = chunk->hash[E];
		chunk->temp[F] = chunk->hash[F];
		chunk->temp[G] = chunk->hash[G];
		chunk->temp[H] = chunk->hash[H];
	}
	else if (type == OFFLOAD)
	{
		chunk->hash[A] += chunk->temp[A];
		chunk->hash[B] += chunk->temp[B];
		chunk->hash[C] += chunk->temp[C];
		chunk->hash[D] += chunk->temp[D];
		chunk->hash[E] += chunk->temp[E];
		chunk->hash[F] += chunk->temp[F];
		chunk->hash[G] += chunk->temp[G];
		chunk->hash[H] += chunk->temp[H];
	}
}
