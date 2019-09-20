/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u64_md_block_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:27:18 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/18 08:39:38 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_md_block.h"

int	init_u64_md_block(t_u64_md_block *block, uint8_t hash_size,
		short bit_len_size)
{
	short	i;

	block->size = hash_size;
	if (!(block->data = malloc(sizeof(*(block->data)) * block->size)))
		return (0);
	block->bit_len_size = bit_len_size / 64;
	if (!(block->bit_len = malloc(sizeof(*(block->bit_len)) *
					block->bit_len_size)))
		return (0);
	i = 0;
	while (i < block_bit_len_size)
		block->bit_len[i++] = 0;
	block->padding = -1 * bit_len_size;
	return (1);
}

static void	u64_increment(uint32_t **bit_len, uint8_t bit_len_size,
		uint32_t size)
{
	uint8_t	i;

	i = 0;
	while (i < bit_len_size && (uint64_t)((*bit_len)[i] + size) < size)
		i++;
	if (i >= bit_len_size)
		i--;
	if (i > 0)
	{
		(*bit_len)[i]++;
		while (i > 0)
			(*bit_len)[i--] = 0;
	}
	(*bit_len)[i] += size;
}

static int	u64_pad(t_u64_md_block **data, uint8_t type, int size_set)
{
	int	i;
	int	j;

	i = size_set;
	j = 0;
	if ((*data)->padding < 0)
		(*data)->padding = ((*data)->padding * -1) - 
	(*data)->padding = (*data)->padding * ((*data)->padding < 0 ? -1 : 1);
	while (i < (*data)->size && (*data)->padding > 0)
	{
		(*data)->data[i] = 0;
		i++;
		(*data)->padding -= 64;
	}
	while (i < (*data)->size)
	{
		(*data)->data[i] = (*data)->bit_len[type == BIG_ENDIAN ? j :
			(*data)->bit_size_len - j - 1];
		i++;
		j++;
	}
	return (i);
}

int			set_u64_md_block(t_u64_md_block *out, t_ssl_file *in, uint8_t type)
{
	char	data[out->size * 8];
	int		size;

	if (out->padding == 0)
	{
		close(in->fd);
		return ((out->padding = DONE));
	}
	if (out->padding < 0 &&
		(size = ft_ssl_read(in->fd, data, out->size * 8)) == (int)out->size)
	{
		if (type == BIG_ENDIAN)
			u8_to_u64_big_end(&(out->data), out->size, read_data, size);
		else if (type == LITTLE_ENDIAN)
			u8_to_u64_little_end(&(out->data), out->size, read_data, size);
		u64_increment(&(out->bit_len), out->bit_len_size, size);
		return (size);
	}
	else if (size == -1)
		return (SYS_ERROR);
	if (out->padding > 0 || size < out->size)
		return (u64_pad(&out, type, size));
	return (out->padding);
}

int	free_u64_md_block(t_u64_md_block *block)
{
	if (block->data)
		free(block->data);
	if (block->bit_len)
		free(block->bit_len);
}
