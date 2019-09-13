/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512_224.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:05:35 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/06 12:16:03 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <limits.h>
#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_sha512.h"
#include "ft_string.h"

#define ONLOAD 1
#define OFFLOAD 2

static uint64_t	pad_data(char *data, t_sha512_chunk *chunk)
{
	uint64_t	len;
	uint64_t	i;

	len = ft_strlen(data);
	i = (len * 8) + 129;
	chunk->len = (i + (1024 - (i % 1024))) / 64;
	if ((chunk->data = malloc(sizeof(*chunk->data) * chunk->len)))
	{
		i = ft_ssl_prep_8b_big_end(&(chunk->data), data, len);
		chunk->data[i++] += ULLONG_LEADING_ONE >> ((len % 8) * 8);
		while (i < chunk->len - 2)
			chunk->data[i++] = 0;
		chunk->data[i++] = FIRST_LEN(len) * 8;
		chunk->data[i] = len * 8;
	}
	return (chunk->len);
}

static void		init_message_schedule(t_sha512_chunk *chunk)
{
	uint8_t	i;

	i = 0;
	while (i < 16)
	{
		chunk->s[i] = chunk->data[chunk->pos + i];
		i++;
	}
	while (i < 80)
	{
		chunk->s[i] = sha512message_schedule_sum(chunk->s, i, S1) +
			chunk->s[i - 7] + sha512message_schedule_sum(chunk->s, i, S0) +
			chunk->s[i - 16];
		i++;
	}
}

static void		compress(t_sha512_chunk *chunk)
{
	uint8_t		i;
	uint64_t	temp1;
	uint64_t	temp2;

	i = 0;
	while (i < 80)
	{
		temp1 = sha512compression_sum(chunk, S1) + sha512choice(chunk) +
			chunk->temp[H] + chunk->s[i] + g_sha512_tab[i];
		temp2 = sha512compression_sum(chunk, S0) + sha512majority(chunk);
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

static void		update_message_schedule(t_sha512_chunk *chunk, uint8_t type)
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

void			ft_ssl_sha512_256(char *data, uint32_t **file_hash)
{
	t_sha512_chunk	chunk;

	pad_data(data, &chunk);
	chunk.pos = 0;
	chunk.hash[A] = 0x22312194FC2BF72C;
	chunk.hash[B] = 0x9F555FA3C84C64C2;
	chunk.hash[C] = 0x2393B86B6F53B151;
	chunk.hash[D] = 0x963877195940EABD;
	chunk.hash[E] = 0x96283EE2A88EFFE3;
	chunk.hash[F] = 0xBE5E1E2553863992;
	chunk.hash[G] = 0x2B0199FC2C85B8AA;
	chunk.hash[H] = 0x0EB72DDC81C52CA2;
	while (chunk.pos < chunk.len)
	{
		init_message_schedule(&chunk);
		update_message_schedule(&chunk, ONLOAD);
		compress(&chunk);
		update_message_schedule(&chunk, OFFLOAD);
		chunk.pos += 16;
	}
	set_8b_to_4b_file_hash(chunk.hash, file_hash, 4);
	free(chunk.data);
}
