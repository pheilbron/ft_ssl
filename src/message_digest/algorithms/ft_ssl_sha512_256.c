/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512_224.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 12:05:35 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/23 16:28:26 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_sha512.h"
#include "ft_ssl_md_block.h"

static int	ft_ssl_sha512_256_buffer(char *data, char **hash)
{
	t_sha512_chunk	chunk;

	if (!init_u64_md_block(&(chunk.block), 16, 128))
		return (0);
	chunk.buf_len = md_pad_u8_to_u64(data, chunk.block.data, BIG_END);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0x22312194FC2BF72C;
	chunk.hash[B] = 0x9F555FA3C84C64C2;
	chunk.hash[C] = 0x2393B86B6F53B151;
	chunk.hash[D] = 0x963877195940EABD;
	chunk.hash[E] = 0x96283EE2A88EFFE3;
	chunk.hash[F] = 0xBE5E1E2553863992;
	chunk.hash[G] = 0x2B0199FC2C85B8AA;
	chunk.hash[H] = 0x0EB72DDC81C52CA2;
	while (chunk.buf_pos < chunk.buf_len)
	{
		init_sha512_message_schedule(&chunk);
		update_sha512_message_schedule(&chunk, ONLOAD);
		compress_sha512_chunk(&chunk);
		update_sha512_message_schedule(&chunk, OFFLOAD);
		chunk.buf_pos += 16;
	}
	if ((*hash = malloc(sizeof(**hash) * (4 * 8 + 1))))
		u64_be_to_u8(chunk.hash, (uint8_t **)hash, 4);
	return (free_u64_md_block(&(chunk.block)));
}

int			ft_ssl_sha512_256(void *data, char **hash, uint8_t type)
{
	t_sha512_chunk	chunk;
	int				status;

	if (type == MD_BUFFER)
		return (ft_ssl_sha512_256_buffer(data, hash));
	if (!init_u64_md_block(&(chunk.block), 16, 128))
		return (0);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0x22312194FC2BF72C;
	chunk.hash[B] = 0x9F555FA3C84C64C2;
	chunk.hash[C] = 0x2393B86B6F53B151;
	chunk.hash[D] = 0x963877195940EABD;
	chunk.hash[E] = 0x96283EE2A88EFFE3;
	chunk.hash[F] = 0xBE5E1E2553863992;
	chunk.hash[G] = 0x2B0199FC2C85B8AA;
	chunk.hash[H] = 0x0EB72DDC81C52CA2;
	while ((status = set_u64_md_block(&(chunk.block), data, BIG_END)) > 0)
	{
		init_sha512_message_schedule(&chunk);
		update_sha512_message_schedule(&chunk, ONLOAD);
		compress_sha512_chunk(&chunk);
		update_sha512_message_schedule(&chunk, OFFLOAD);
	}
	if (status == DONE && (*hash = malloc(sizeof(**hash) * (4 * 8 + 1))))
		u64_be_to_u8(chunk.hash, (uint8_t **)hash, 4);
	return (free_u64_md_block(&(chunk.block)));
}
