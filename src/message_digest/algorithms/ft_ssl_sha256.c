/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 16:05:48 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 15:47:35 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_sha256.h"
#include "ft_string.h"

#define ONLOAD 1
#define OFFLOAD 2

uint32_t g_sha256_tab[] = {0x428a2f98, 0x71374491, 0xb5c0fbcf, 0xe9b5dba5,
	0x3956c25b, 0x59f111f1, 0x923f82a4, 0xab1c5ed5, 0xd807aa98, 0x12835b01,
	0x243185be, 0x550c7dc3, 0x72be5d74, 0x80deb1fe, 0x9bdc06a7, 0xc19bf174,
	0xe49b69c1, 0xefbe4786, 0x0fc19dc6, 0x240ca1cc, 0x2de92c6f, 0x4a7484aa,
	0x5cb0a9dc, 0x76f988da, 0x983e5152, 0xa831c66d, 0xb00327c8, 0xbf597fc7,
	0xc6e00bf3, 0xd5a79147, 0x06ca6351, 0x14292967, 0x27b70a85, 0x2e1b2138,
	0x4d2c6dfc, 0x53380d13, 0x650a7354, 0x766a0abb, 0x81c2c92e, 0x92722c85,
	0xa2bfe8a1, 0xa81a664b, 0xc24b8b70, 0xc76c51a3, 0xd192e819, 0xd6990624,
	0xf40e3585, 0x106aa070, 0x19a4c116, 0x1e376c08, 0x2748774c, 0x34b0bcb5,
	0x391c0cb3, 0x4ed8aa4a, 0x5b9cca4f, 0x682e6ff3, 0x748f82ee, 0x78a5636f,
	0x84c87814, 0x8cc70208, 0x90befffa, 0xa4506ceb, 0xbef9a3f7, 0xc67178f2};

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

	i = 0;
	while (i < 64)
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
		i++;
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

void			ft_ssl_sha256(char *data, uint32_t **file_hash)
{
	t_sha256_chunk	chunk;

	pad_data(data, &chunk);
	chunk.pos = 0;
	chunk.hash[A] = 0x6a09e667;
	chunk.hash[B] = 0xbb67ae85;
	chunk.hash[C] = 0x3c6ef372;
	chunk.hash[D] = 0xa54ff53a;
	chunk.hash[E] = 0x510e527f;
	chunk.hash[F] = 0x9b05688c;
	chunk.hash[G] = 0x1f83d9ab;
	chunk.hash[H] = 0x5be0cd19;
	while (chunk.pos < chunk.len)
	{
		init_message_schedule(&chunk);
		update_message_schedule(&chunk, ONLOAD);
		compress(&chunk);
		update_message_schedule(&chunk, OFFLOAD);
		chunk.pos += 16;
	}
	set_4b_file_hash(chunk.hash, file_hash, 8);
	free(chunk.data);
}
