/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha224.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:45:47 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 15:48:00 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_sha256.h"
#include "ft_string.h"

#define ONLOAD 1
#define OFFLOAD 2

static uint32_t	pad_data(char *data, t_sha256_chunk *chunk)
{
	uint64_t	len;
	uint64_t	i;

	len = ft_strlen(data);
	i = (len * 8) + 65;
	chunk->len = (i + (512 - (i % 512))) / 32;
	if ((chunk->data = malloc(sizeof(*chunk->data) * chunk->len)))
	{
		i = ft_ssl_prep_4b_big_end(&(chunk->data), data, len);
		chunk->data[i++] += ULONG_LEADING_ONE >> ((len % 4) * 8);
		while (i < chunk->len - 2)
			chunk->data[i++] = 0;
		chunk->data[i++] = (uint32_t)(FIRST_HALF(len * 8));
		chunk->data[i] = (uint32_t)(SECOND_HALF(len * 8));
	}
	return (chunk->len);
}

static void		init_message_schedule(t_sha256_chunk *chunk)
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

static void		compress(t_sha256_chunk *chunk)
{
	uint8_t		i;
	uint32_t	temp1;
	uint32_t	temp2;

	i = -1;
	while (++i < 64)
	{
		temp1 = compression_sum(chunk, S1) + choice(chunk) + chunk->temp[H] +
			chunk->s[i] + g_sha256_tab[i];
		temp2 = compression_sum(chunk, S0) + majority(chunk);
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

static void		update_message_schedule(t_sha256_chunk *chunk, uint8_t type)
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

void			ft_ssl_sha224(char *data, uint32_t **file_hash)
{
	t_sha256_chunk	chunk;

	pad_data(data, &chunk);
	chunk.pos = 0;
	chunk.hash[A] = 0xc1059ed8;
	chunk.hash[B] = 0x367cd507;
	chunk.hash[C] = 0x3070dd17;
	chunk.hash[D] = 0xf70e5939;
	chunk.hash[E] = 0xffc00b31;
	chunk.hash[F] = 0x68581511;
	chunk.hash[G] = 0x64f98fa7;
	chunk.hash[H] = 0xbefa4fa4;
	while (chunk.pos < chunk.len)
	{
		init_message_schedule(&chunk);
		update_message_schedule(&chunk, ONLOAD);
		compress(&chunk);
		update_message_schedule(&chunk, OFFLOAD);
		chunk.pos += 16;
	}
	set_4b_file_hash(chunk.hash, file_hash, 7);
	free(chunk.data);
}
