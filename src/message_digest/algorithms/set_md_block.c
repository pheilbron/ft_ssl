/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   set_md_block.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 14:33:49 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 16:31:18 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md_block.h"


int	ft_ssl_init_u32_md_block(t_u32_md_block *block, uint8_t hash_size,
		short bit_len_size)
{
	short	i;

	block->size = hash_size;
	if (!(block->data = malloc(sizeof(*(block->data)) * block->size)))
		return (0);
	block->bit_len_size = bit_len_size / 32;
	if (!(block->bit_len = malloc(sizeof(*(block->bit_len)) *
					block->bit_len_size)))
		return (0);
	i = 0;
	while (i < block_bit_len_size)
		block->bit_len[i++] = 0;
	block->padding = -1 * bit_len_size;
	return (1);
}

static int	ft_ssl_read(int fd, char *buf, int size);

int			ft_ssl_set_u32_md_block(t_u32_md_block *out, t_ssl_file *in,
		uint8_t type)
{
	char	data[out->size * 4];
	int		size;

	if (out->padding < 0 && in->fd == 0)
	if (out->padding < 0 &&
		(size = ft_ssl_read(in->fd, data, out->size * 4)) == (int)out->size)
	{
		if (type == BIG_ENDIAN)
			u8_to_u32_big_end(&(out->data), out->size, read_data, size);
		else if (type == LITTLE_ENDIAN)
			u8_to_u32_little_end(&(out->data), out->size, read_data, size);
		u32_increment(&(out->bit_len), out->bit_len_size, size);
		return (1);
	}
	else if (size == -1)
		return (SYS_ERROR);
	else if (size < (int)out->size)
		//set padding value
	if (out->padding >= 0)
		//set padding and len (if possible)
	return (out->padding);
}
