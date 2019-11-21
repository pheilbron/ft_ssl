/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:47:56 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/21 12:11:15 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_utils.h"
#include "ft_ssl_sha1.h"
#include "ft_ssl_md_block.h"

uint32_t	g_sha1_tab[] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};

static void		init_message_schedule(t_sha1_chunk *chunk)
{
	uint8_t	i;

	i = 0;
	while (i < 16)
	{
		chunk->s[i] = chunk->block.data[chunk->buf_pos + i];
		i++;
	}
	while (i < 80)
	{
		chunk->s[i] = rot_l(chunk->s[i - 3] ^ chunk->s[i - 8] ^
				chunk->s[i - 14] ^ chunk->s[i - 16], 1, 32);
		i++;
	}
}

static void		update_temp(t_sha1_chunk *ch, uint32_t i)
{
	uint32_t	temp;

	if (i < 20)
		temp = (ch->temp[B] & ch->temp[C]) | (~(ch->temp[B]) & ch->temp[D]);
	else if ((i > 19 && i < 40) || (i > 59 && i < 80))
		temp = (ch->temp[B] ^ ch->temp[C] ^ ch->temp[D]);
	else
		temp = (ch->temp[B] & ch->temp[C]) | (ch->temp[B] & ch->temp[D]) |
			(ch->temp[C] & ch->temp[D]);
	temp += (uint32_t)rot_l(ch->temp[A], 5, 32) + ch->temp[E] +
		g_sha1_tab[i / 20] + ch->s[i];
	ch->temp[E] = ch->temp[D];
	ch->temp[D] = ch->temp[C];
	ch->temp[C] = rot_l(ch->temp[B], 30, 32);
	ch->temp[B] = ch->temp[A];
	ch->temp[A] = temp;
}

static void		set_block(t_sha1_chunk *chunk)
{
	uint32_t	i;

	i = 0;
	chunk->temp[A] = chunk->hash[A];
	chunk->temp[B] = chunk->hash[B];
	chunk->temp[C] = chunk->hash[C];
	chunk->temp[D] = chunk->hash[D];
	chunk->temp[E] = chunk->hash[E];
	while (i < 80)
		update_temp(chunk, i++);
	chunk->hash[A] += chunk->temp[A];
	chunk->hash[B] += chunk->temp[B];
	chunk->hash[C] += chunk->temp[C];
	chunk->hash[D] += chunk->temp[D];
	chunk->hash[E] += chunk->temp[E];
}

int				ft_ssl_sha1_file(t_ssl_file *file, char **hash)
{
	t_sha1_chunk	chunk;
	int			status;

	if (!init_u32_md_block(&(chunk.block), 16, 64, MD_FILE))
		return (0);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0x67452301;
	chunk.hash[B] = 0xefcdab89;
	chunk.hash[C] = 0x98badcfe;
	chunk.hash[D] = 0x10325476;
	chunk.hash[E] = 0xc3d2e1f0;
	while ((status = set_u32_md_block(&(chunk.block), file, BIG_END)) > 0)
	{
		init_message_schedule(&chunk);
		set_block(&chunk);
	}
	if (status == DONE && (*hash = malloc(sizeof(**hash) * (5 * 8 + 1))))
		u32_be_to_u8(chunk.hash, (uint8_t **)hash, 5);
	return (free_u32_md_block(&(chunk.block)));
}

int			ft_ssl_sha1_buffer(char *data, char **hash)
{
	t_sha1_chunk	chunk;

	if (!init_u32_md_block(&(chunk.block), 16, 64, MD_BUFFER))
		return (0);
	chunk.buf_len = md_pad_u8_to_u32(data, &chunk.block.data, BIG_END);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0x67452301;
	chunk.hash[B] = 0xefcdab89;
	chunk.hash[C] = 0x98badcfe;
	chunk.hash[D] = 0x10325476;
	chunk.hash[E] = 0xc3d2e1f0;
	while (chunk.buf_pos < chunk.buf_len)
	{
		init_message_schedule(&chunk);
		set_block(&chunk);
		chunk.buf_pos += 16;
	}
	if ((*hash = malloc(sizeof(**hash) * (5 * 8 + 1))))
		u32_be_to_u8(chunk.hash, (uint8_t **)hash, 5);
	return (free_u32_md_block(&(chunk.block)));
}

int				ft_ssl_sha1(void *data, char **hash, uint16_t type)
{
	t_sha1_chunk	chunk;
	int			status;

	if (type == MD_BUFFER)
		return (ft_ssl_sha1_buffer(data, hash));
	if (!init_u32_md_block(&(chunk.block), 16, 64, MD_FILE))
		return (0);
	chunk.buf_pos = 0;
	chunk.hash[A] = 0x67452301;
	chunk.hash[B] = 0xefcdab89;
	chunk.hash[C] = 0x98badcfe;
	chunk.hash[D] = 0x10325476;
	chunk.hash[E] = 0xc3d2e1f0;
	while ((status = set_u32_md_block(&(chunk.block), data, BIG_END)) > 0)
	{
		init_message_schedule(&chunk);
		set_block(&chunk);
	}
	if (status == DONE && (*hash = malloc(sizeof(**hash) * (5 * 8 + 1))))
		u32_be_to_u8(chunk.hash, (uint8_t **)hash, 5);
	return (free_u32_md_block(&(chunk.block)));
}
