/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u32_md_block_utils.c                               :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 14:25:46 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 13:45:13 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <unistd.h>
#include "ft_ssl.h"
#include "ft_ssl_md_block.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_utils.h"
#include "read_data.h"
#include <unistd.h>
#include "read_data.h"
#include "ft_string.h"
#include "ft_math.h"

int	u8_to_u32_be(uint8_t *in, uint32_t **out, int len)
{
	int	in_i;
	int	out_i;

	in_i = 0;
	out_i = 0;
	(*out)[out_i] = 0;
	while (in_i < len)
	{
		(*out)[out_i] += (((uint32_t)(in[in_i])) <<
				((3 - (in_i % 4)) * 8));
		if (in_i % 4 == 3)
			(*out)[++out_i] = 0;
		in_i++;
	}
	return (out_i);
}
int	ft_ssl_read(int fd, char *buf, int size)
{
	static struct s_holder	h = {{'\0'}, 0, 0};
	char					read_buf[BUF_SIZE];
	int						total;
	int						ret;

	total = 0;
	ret = 1;
	if ((h.len - h.i) > 0)
	{
		printf("total: %d\t h.len: %d\t h.i: %d\n", total, h.len, h.i);
		ft_memcpy(buf, h.buf + h.i, (total = ft_min(h.len - h.i, size)));
		printf("total: %d\t h.len: %d\t h.i: %d\n", total, h.len, h.i);
		h.i = (total > size ? 0 : h.i + total);
		printf("total: %d\t h.len: %d\t h.i: %d\n", total, h.len, h.i);
	}
	if (total < size)
	{
		if ((ret = read(fd, buf, size)) == size)
			return ((h.len = read(fd, h.buf, BUF_SIZE)) > 0 ? ret : h.len);
		while ((total += ret) < size && ret > 0)
			if ((ret = read(fd, read_buf, size - total)) > 0)
				ft_memcpy(buf + total, read_buf, size - total);
		if (ret > 0)
			h.len = read(fd, h.buf, BUF_SIZE);
	}
//	return (total <= size ? total : ret);
	return (ret < 1 ? ret + total : total);
}

int			init_u32_md_block(t_u32_md_block *block, uint8_t hash_size,
		short bit_len_size, uint8_t type)
{
	short	i;

	block->size = hash_size;
	if (type == MD_FILE && 
			!(block->data = malloc(sizeof(*(block->data)) * block->size)))
		return (0);
	block->bit_len_size = bit_len_size / 32;
	if (!(block->bit_len = malloc(sizeof(*(block->bit_len)) *
					block->bit_len_size)))
		return (0);
	i = 0;
	while (i < block->bit_len_size)
		block->bit_len[i++] = 0;
	block->padding = hash_size * 32 * -2;
	return (1);
}

static void	u32_increment(uint32_t **bit_len, uint8_t bit_len_size,
		uint32_t size)
{
	uint8_t	i;

	i = 0;
	while (i < bit_len_size && (uint32_t)((*bit_len)[i] + size) < size)
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

#define U32_LE_PAD_ONE(x) (1UL << 31) >> ((3 - (x % 4)) * 8)
#define U32_BE_PAD_ONE(x) (1UL << 31) >> ((x % 4) * 8)

static int	u32_pad(t_u32_md_block **data, uint8_t type, int size_set)
{
	int	i;
	int	j;

	i = size_set / 4;
	j = 0;
	if (size_set % 4 == 0)
		(*data)->data[i] = 0;
	if ((*data)->padding < 0)
	{
		(*data)->padding = (((*data)->padding + (size_set * 8) +
					((size_set * 8 + 8) % 32) +
					(*data)->bit_len_size * 32 + 8) * -1) % ((*data)->size * 32);
		(*data)->data[i++] += (type == LE ? U32_LE_PAD_ONE(size_set) :
				U32_BE_PAD_ONE(size_set));
		(*data)->padding -= ((*data)->padding % 32);
	}
	printf("new padding: %d\n", (*data)->padding);
	while (i < (*data)->size && (*data)->padding > 0)
	{
		(*data)->data[i] = 0;
		i++;
		(*data)->padding -= 32;
	}
	while (i < (*data)->size)
	{
		printf("size\n");
		(*data)->data[i] = (*data)->bit_len[type == BIG_END ? j :
			(*data)->bit_len_size - j - 1];
		i++;
		j++;
	}
	return (i);
}

int			set_u32_md_block(t_u32_md_block *out, t_ssl_file *in, uint8_t type)
{
	char	data[out->size * 4];
	int		size;

	if (out->padding == 0)
	{
		close(in->fd);
		return ((out->padding = DONE));
	}
	if (((size = ft_ssl_read(in->fd, data, out->size * 4)) > 0) &&
			out->padding < 0)
	{
		type == BIG_END ? u8_to_u32_be((uint8_t *)data, &(out->data), size) :
			u8_to_u32_le((uint8_t *)data, &(out->data), size);
		u32_increment(&(out->bit_len), out->bit_len_size, size);
		if (size == (int)(out->size * 4))
			return (size);
	}
	else if (size == -1)
		return (SYS_ERROR);
	if (out->padding > 0 || size < (int)(out->size * 4))
		return (u32_pad(&out, type, size));
	return (out->padding * -1);
}

int			free_u32_md_block(t_u32_md_block *block)
{
	if (block->data)
		free(block->data);
	if (block->bit_len)
		free(block->bit_len);
	return (1);
}

int	u8_to_u32_le(uint8_t *in, uint32_t **out, int len)
{
	int	in_i;
	int	out_i;

	in_i = 0;
	out_i = 0;
	(*out)[out_i] = 0;
	while (in_i < len)
	{
		if (in_i % 4 == 0)
			(*out)[out_i] = 0;
		(*out)[out_i] |= (((uint32_t)(in[in_i])) <<
				((in_i % 4) * 8));
		if (in_i % 4 == 3)
			out_i++;
		in_i++;
	}
	return (out_i);
}

#include <stdio.h>
#include <fcntl.h>
int	main(void)
{
	t_u32_md_block	test;
	t_ssl_file	*file = malloc(sizeof(*file));
	int status;
	file->fd = open("test_file", O_RDONLY);
	file->reference = "test_file";
	file->e.no = 1;
	init_u32_md_block(&test, 16, 64, MD_FILE);
	char	buf[test.size * 4];
	printf("padding: %d\n", test.padding);
	int i = 0;
//	while ((status = ft_ssl_read(file->fd, buf, test.size * 4)) > 0)
//	{
//		write(1, buf, status);
//		write(1, "\n", 1);
//		i++;
//		if (i == 4)
//			break ;
//	}
	while ((status = set_u32_md_block(&test, file, LITTLE_END)) > 0)
	{
		for (int i = 0; i < test.size; i++)
			printf("\t%x\n", test.data[i]);
		printf("padding: %d\n", test.padding);
		printf("\n");
		i++;
		if (i == 4)
			break ;
	}
	if (status == DONE)
		printf("DONE\n");
	return (0);
}
