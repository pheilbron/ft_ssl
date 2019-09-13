/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 22:02:22 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 15:44:19 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha256.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_sha_aux.h"

static uint32_t	message_schedule_sum(uint32_t message_schedule[64],
		uint8_t offset, uint8_t type)
{
	if (type == S0)
		return (rot_r(message_schedule[offset - 2], 17, 32) ^
				rot_r(message_schedule[offset - 2], 19, 32) ^
				(message_schedule[offset - 2] >> 10));
	if (type == S1)
		return (rot_r(message_schedule[offset - 15], 7, 32) ^
				rot_r(message_schedule[offset - 15], 18, 32) ^
				(message_schedule[offset - 15] >> 3));
	return (0);
}

static uint32_t	compression_sum(t_sha256_chunk *c, uint8_t type)
{
	if (type == S0)
		return (rot_r(c->temp[A], 2, 32) ^ rot_r(c->temp[A], 13, 32) ^
				rot_r(c->temp[A], 22, 32));
	if (type == S1)
		return (rot_r(c->temp[E], 6, 32) ^ rot_r(c->temp[E], 11, 32) ^
				rot_r(c->temp[E], 25, 32));
	return (0);
}

void			init_sha256_message_schedule(t_sha256_chunk *chunk)
{
	uint8_t	i;

	i = 0;
	while (i < 16)
	{
		chunk->s[i] = chunk->data[chunk->pos + i];
		i++;
	}
	while (i < 64)
	{
		chunk->s[i] = message_schedule_sum(chunk->s, i, S1) +
			chunk->s[i - 7] + message_schedule_sum(chunk->s, i, S0) +
			chunk->s[i - 16];
		i++;
	}
}

void			compress_sha256_chunk(t_sha256_chunk *chunk)
{
	uint8_t		i;
	uint32_t	temp1;
	uint32_t	temp2;

	i = -1;
	while (++i < 64)
	{
		temp1 = compression_sum(chunk, S1) +
			u32_ch(chunk->temp[E], chunk->temp[F], chunk->temp[G]) +
			chunk->temp[H] + chunk->s[i] + g_sha256_tab[i];
		temp2 = compression_sum(chunk, S0) +
			u32_maj(chunk->temp[A], chunk->temp[B], chunk->temp[C]);
		chunk->temp[H] = chunk->temp[G];
		chunk->temp[G] = chunk->temp[F];
		chunk->temp[F] = chunk->temp[E];
		chunk->temp[E] = chunk->temp[D] + temp1;
		chunk->temp[D] = chunk->temp[C];
		chunk->temp[C] = chunk->temp[B];
		chunk->temp[B] = chunk->temp[A];
		chunk->temp[A] = temp1 + temp2;
	}
}

void			update_sha256_message_schedule(t_sha256_chunk *chunk,
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
