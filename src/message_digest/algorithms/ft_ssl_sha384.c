/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:26:46 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 18:06:09 by pheilbro         ###   ########.fr       */
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
//		printf("compression_sum1: %llu\tchoice: %llu\tH: %llu\tMS[i]: %llu\t",
//				sha512compression_sum(chunk, S1), sha512choice(chunk),
//				chunk->temp[H], chunk->s[i]);
//		printf("K[i]: %llu\t\ttemp1: %llu\n\n", g_sha512_tab[i], temp1);
		chunk->temp[H] = chunk->temp[G];
		chunk->temp[G] = chunk->temp[F];
		chunk->temp[F] = chunk->temp[E];
		chunk->temp[E] = chunk->temp[D] + temp1;
		chunk->temp[D] = chunk->temp[C];
		chunk->temp[C] = chunk->temp[B];
		chunk->temp[B] = chunk->temp[A];
		chunk->temp[A] = temp1 + temp2;
//		printf("t=%2d: %.16llX %.16llX %.16llX %.16llX %.16llX %.16llX %.16llX %.16llX\n", i,
//				chunk->temp[A], chunk->temp[B], chunk->temp[C], chunk->temp[D],
//				chunk->temp[E], chunk->temp[F], chunk->temp[G], chunk->temp[H]);
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

void			ft_ssl_sha384(char *data, uint32_t **file_hash)
{
	t_sha512_chunk	chunk;

	pad_data(data, &chunk);
//	for (size_t a = 0; a < chunk.len; a++)
//		printf("%.16llx\t%llu\n", chunk.data[a], chunk.data[a]);
	chunk.pos = 0;
	chunk.hash[A] = 0xcbbb9d5dc1059ed8;
	chunk.hash[B] = 0x629a292a367cd507;
	chunk.hash[C] = 0x9159015a3070dd17;
	chunk.hash[D] = 0x152fecd8f70e5939;
	chunk.hash[E] = 0x67332667ffc00b31;
	chunk.hash[F] = 0x8eb44a8768581511;
	chunk.hash[G] = 0xdb0c2e0d64f98fa7;
	chunk.hash[H] = 0x47b5481dbefa4fa4;
	while (chunk.pos < chunk.len)
	{
		init_message_schedule(&chunk);
		update_message_schedule(&chunk, ONLOAD);
		compress(&chunk);
		update_message_schedule(&chunk, OFFLOAD);
		chunk.pos += 16;
	}
	set_8b_to_4b_file_hash(chunk.hash, file_hash, 6);
	free(chunk.data);
}
