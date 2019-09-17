/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha384.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 13:41:36 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 13:56:21 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_sha512.h"
#include "ft_ssl_md_block.h"

void			ft_ssl_sha512_file(t_ssl_file *file, char **hash)
{
	t_sha512_chunk	chunk;
	int				status;

	if (!init_u64_md_block(&(chunk.block), 16, 128))
		return (0);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0xcbbb9d5dc1059ed8;
	chunk.hash[B] = 0x629a292a367cd507;
	chunk.hash[C] = 0x9159015a3070dd17;
	chunk.hash[D] = 0x152fecd8f70e5939;
	chunk.hash[E] = 0x67332667ffc00b31;
	chunk.hash[F] = 0x8eb44a8768581511;
	chunk.hash[G] = 0xdb0c2e0d64f98fa7;
	chunk.hash[H] = 0x47b5481dbefa4fa4;
	while ((status = set_u64_md_block(&(chunk.block), file, BIG_ENDIAN)) > 0)
	{
		init_sha512_block_message_schedule(&chunk);
		update_sha512_message_schedule(&chunk, ONLOAD);
		compress_sha512_chunk(&chunk);
		update_sha512_message_schedule(&chunk, OFFLOAD);
	}
	if (status == DONE && (*hash = malloc(sizeof(**hash) * (6 * 8 + 1))))
		u64_be_to_u8(chunk.hash, hash, 6);
	return (free_u64_md_block(&(chunk.block)));
}

void			ft_ssl_sha384_buffer(char *data, char **hash)
{
	t_sha512_chunk	chunk;

	if (!init_u64_md_block(&(chunk.block), 16, 128))
		return (0);
	chunk.buf_len = md_pad_u8_to_u64(data, chunk.block.data, BIG_ENDIAN);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0xcbbb9d5dc1059ed8;
	chunk.hash[B] = 0x629a292a367cd507;
	chunk.hash[C] = 0x9159015a3070dd17;
	chunk.hash[D] = 0x152fecd8f70e5939;
	chunk.hash[E] = 0x67332667ffc00b31;
	chunk.hash[F] = 0x8eb44a8768581511;
	chunk.hash[G] = 0xdb0c2e0d64f98fa7;
	chunk.hash[H] = 0x47b5481dbefa4fa4;
	while (chunk.buf_pos < chunk.buf_len)
	{
		init_sha512_block_message_schedule(&chunk);
		update_sha512_message_schedule(&chunk, ONLOAD);
		compress_sha512_chunk(&chunk);
		update_sha512_message_schedule(&chunk, OFFLOAD);
		chunk.buf_pos += 16;
	}
	if ((*hash = malloc(sizeof(**hash) * (6 * 8 + 1))))
		u64_be_to_u8(chunk.hash, hash, 6);
	return (free_u64_md_block(&(chunk.block)));
}
