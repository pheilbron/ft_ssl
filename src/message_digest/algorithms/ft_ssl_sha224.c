/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha224.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 13:45:47 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 13:41:53 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_sha256.h"
#include "ft_ssl_md_block.h"

int	ft_ssl_sha224_file(t_ssl_file *file, char **hash)
{
	t_sha256_chunk	chunk;
	int				status;

	if (!init_u32_md_block(&(chunk.block), 16, 64))
		return (0);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0xc1059ed8;
	chunk.hash[B] = 0x367cd507;
	chunk.hash[C] = 0x3070dd17;
	chunk.hash[D] = 0xf70e5939;
	chunk.hash[E] = 0xffc00b31;
	chunk.hash[F] = 0x68581511;
	chunk.hash[G] = 0x64f98fa7;
	chunk.hash[H] = 0xbefa4fa4;
	while ((status = set_u32_md_block(&(chunk.block), file, BIG_ENDIAN)) > 0)
	{
		init_sha256_block_message_schedule(&chunk);
		update_sha256_message_schedule(&chunk, ONLOAD);
		compress_sha256_chunk(&chunk);
		update_sha256_message_schedule(&chunk, OFFLOAD);
	}
	if (status == DONE && (*hash = malloc(sizeof(**hash) * (7 * 4 + 1))))
		u32_be_to_u8(chunk.hash, hash, 7);
	return (free_u32_md_block(&(chunk.block)));
}

int	ft_ssl_sha224_buffer(char *data, char **hash)
{
	t_sha256_chunk	chunk;

	if (!init_u32_md_block(&(chunk.block), 16, 64))
		return (0);
	chunk.buf_len = md_pad_u8_to_u32(data, chunk.block.data, BIG_ENDIAN);
	chunk.buf_pos = 0;
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
		init_sha256_block_message_schedule(&chunk);
		update_sha256_message_schedule(&chunk, ONLOAD);
		compress_sha256_chunk(&chunk);
		update_sha256_message_schedule(&chunk, OFFLOAD);
	}
	if ((*hash = malloc(sizeof(**hash) * (7 * 4 + 1))))
		u32_be_to_u8(chunk.hash, hash, 7);
	return (free_u32_md_block(&(chunk.block)));
}
