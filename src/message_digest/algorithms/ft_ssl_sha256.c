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

int	ft_ssl_sha256_file(t_ssl_file *file, char **hash)
{
	t_sha256_chunk	chunk;
	int				pass;

	if (!init_u32_md_block(&(chunk.block), 16, 64))
		return (0);
	chunk.hash[A] = 0x6a09e667;
	chunk.hash[B] = 0xbb67ae85;
	chunk.hash[C] = 0x3c6ef372;
	chunk.hash[D] = 0xa54ff53a;
	chunk.hash[E] = 0x510e527f;
	chunk.hash[F] = 0x9b05688c;
	chunk.hash[G] = 0x1f83d9ab;
	chunk.hash[H] = 0x5be0cd19;
	while ((pass = set_u32_md_block(&(chunk.block), file, BIG_ENDIAN)))
	{
		init_sha256_block_message_schedule(&chunk);
		update_sha256_message_schedule(&chunk, ONLOAD);
		compress_sha256_chunk(&chunk);
		update_sha256_message_schedule(&chunk, OFFLOAD);
	}
	if (!pass)
		return (free_u32_md_block(&(chunk.block)));
	if ((*hash = malloc(sizeof(**hash) * (8 * 4 + 1))))
		u32_be_to_u8(chunk.hash, hash, chunk.len);
	return (free_u32_md_block(&(chunk.block)));
}

int	ft_ssl_sha256_buffer(char *data, char **hash)
{
	t_sha256_buffer	chunk;

	chunk.len = md_pad_u8_to_u32(data, chunk.data, BIG_ENDIAN);
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
		init_sha256_block_message_schedule(&chunk);
		update_sha256_message_schedule(&chunk, ONLOAD);
		compress_sha256_chunk(&chunk);
		update_sha256_message_schedule(&chunk, OFFLOAD);
	}
	if ((*hash = malloc(sizeof(**hash) * (8 * 4 + 1))))
		u32_be_to_u8(chunk.hash, hash, chunk.len);
	free(chunk.data);
	return (1);
}
