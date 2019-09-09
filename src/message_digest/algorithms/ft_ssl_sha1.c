/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha1.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:47:56 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 16:02:45 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_sha1.h"
#include "ft_string.h"

uint32_t	g_sha1_tab[] = {0x5a827999, 0x6ed9eba1, 0x8f1bbcdc, 0xca62c1d6};

static uint32_t	pad_data(char *data, t_sha1_chunk *chunk)
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

static void		init_message_schedule(t_sha1_chunk *chunk)
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
		chunk->s[i] = rot_l(chunk->s[i - 3] ^ chunk->s[i - 8] ^
				chunk->s[i - 14] ^ chunk->s[i - 16], 1, 32);
		i++;
	}
}

static void		update_temp(t_sha1_chunk *ch, uint32_t i)
{
	uint32_t	F;

	if (i < 20)
		F = (ch->temp[B] & ch->temp[C]) | (~(ch->temp[B]) & ch->temp[D]);
	else if ((i > 19 && i < 40) || (i > 59 && i < 80))
		F = (ch->temp[B] ^ ch->temp[C] ^ ch->temp[D]);
	else
		F = (ch->temp[B] & ch->temp[C]) | (ch->temp[B] & ch->temp[D]) |
			(ch->temp[C] & ch->temp[D]);
	F += (uint32_t)rot_l(ch->temp[A], 5, 32) + ch->temp[E] + g_sha1_tab[i / 20]
		+ ch->s[i];
	ch->temp[E] = ch->temp[D];
	ch->temp[D] = ch->temp[C];
	ch->temp[C] = rot_l(ch->temp[B], 30, 32);
	ch->temp[B] = ch->temp[A];
	ch->temp[A] = F;
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

void			ft_ssl_sha1(char *data, uint32_t **file_hash)
{
	t_sha1_chunk	chunk;

	pad_data(data, &chunk);
	chunk.pos = 0;
	chunk.hash[A] = 0x67452301;
	chunk.hash[B] = 0xefcdab89;
	chunk.hash[C] = 0x98badcfe;
	chunk.hash[D] = 0x10325476;
	chunk.hash[E] = 0xc3d2e1f0;
	while (chunk.pos < chunk.len)
	{
		init_message_schedule(&chunk);
		set_block(&chunk);
		chunk.pos += 16;
	}
	set_4b_file_hash(chunk.hash, file_hash, 5);
	free(chunk.data);
}
