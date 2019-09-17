/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512_224.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:05:35 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 13:53:08 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_sha512.h"
#include "ft_ssl_md_block.h"
//fix hash size return
void			ft_ssl_sha512_224_file(t_ssl_file *file, char **hash)
{
	t_sha512_chunk	chunk;
	int				status;

	if (!init_u64_md_block(&(chunk.block), 16, 128))
		return (0);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0x8C3D37C819544DA2;
	chunk.hash[B] = 0x73E1996689DCD4D6;
	chunk.hash[C] = 0x1DFAB7AE32FF9C82;
	chunk.hash[D] = 0x679DD514582F9FCF;
	chunk.hash[E] = 0x0F6D2B697BD44DA8;
	chunk.hash[F] = 0x77E36F7304C48942;
	chunk.hash[G] = 0x3F9D85A86A1D36C8;
	chunk.hash[H] = 0x1112E6AD91D692A1;
	while ((status = set_u64_md_block(&(chunk.block), file, BIG_ENDIAN)) > 0)
	{
		init_sha512_block_message_schedule(&chunk);
		update_sha512_message_schedule(&chunk, ONLOAD);
		compress_sha512_chunk(&chunk);
		update_sha512_message_schedule(&chunk, OFFLOAD);
	}
	if (status == DONE && (*hash = malloc(sizeof(**hash) * (4 * 8 + 1))))
		u64_be_to_u8(chunk.hash, hash, 4);
	return (free_u64_md_block(&(chunk.block)));
}

void			ft_ssl_sha512_224_buffer(char *data, char **hash)
{
	t_sha512_chunk	chunk;

	if (!init_u64_md_block(&(chunk.block), 16, 128))
		return (0);
	chunk.buf_len = md_pad_u8_to_u64(data, chunk.block.data, BIG_ENDIAN);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0x8C3D37C819544DA2;
	chunk.hash[B] = 0x73E1996689DCD4D6;
	chunk.hash[C] = 0x1DFAB7AE32FF9C82;
	chunk.hash[D] = 0x679DD514582F9FCF;
	chunk.hash[E] = 0x0F6D2B697BD44DA8;
	chunk.hash[F] = 0x77E36F7304C48942;
	chunk.hash[G] = 0x3F9D85A86A1D36C8;
	chunk.hash[H] = 0x1112E6AD91D692A1;
	while (chunk.buf_pos < chunk.buf_len)
	{
		init_sha512_block_message_schedule(&chunk);
		update_sha512_message_schedule(&chunk, ONLOAD);
		compress_sha512_chunk(&chunk);
		update_sha512_message_schedule(&chunk, OFFLOAD);
		chunk.pos += 16;
	}
	if ((*hash = malloc(sizeof(**hash) * (4 * 8 + 1))))
		u64_be_to_u8(chunk.hash, hash, 4);
	return (free_u64_md_block(&(chunk.block)));
}
