/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u64_md_block_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:27:18 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 19:11:47 by pheilbro         ###   ########.fr       */
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

int	free_u64_md_block(t_u64_md_block *block)
{
	if (block->data)
		free(block->data);
	if (block->bit_len)
		free(block->bit_len);
}
