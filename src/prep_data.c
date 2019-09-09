/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   prep_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/30 18:49:40 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 15:48:48 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

#define BYTE_1_MASK (uint32_t)0xFF000000
#define BYTE_2_MASK (uint32_t)0xFF0000
#define BYTE_3_MASK (uint32_t)0xFF00
#define BYTE_4_MASK (uint32_t)0xFF

int	ft_ssl_prep_4b_little_end(uint32_t **prepped_data, char *data, uint64_t len)
{
	uint64_t data_i;
	int	pdata_i;

	data_i = 0;
	pdata_i = 0;
	(*prepped_data)[pdata_i] = 0;
	while (data_i < len)
	{
		(*prepped_data)[pdata_i] += (((uint32_t)(data[data_i])) <<
				((data_i % 4) * 8));
		if (data_i % 4 == 3)
			(*prepped_data)[++pdata_i] = 0;
		data_i++;
	}
	return (pdata_i);
}

int	ft_ssl_prep_4b_big_end(uint32_t **prepped_data, char *data, uint64_t len)
{
	uint64_t data_i;
	int	pdata_i;

	data_i = 0;
	pdata_i = 0;
	(*prepped_data)[pdata_i] = 0;
	while (data_i < len)
	{
		(*prepped_data)[pdata_i] += (((uint32_t)(data[data_i])) <<
				((3 - (data_i % 4)) * 8));
		if (data_i % 4 == 3)
			(*prepped_data)[++pdata_i] = 0;
		data_i++;
	}
	return (pdata_i);
}

int	ft_ssl_prep_8b_big_end(uint64_t **prepped_data, char *data, uint64_t len)
{
	uint64_t data_i;
	int	pdata_i;

	data_i = 0;
	pdata_i = 0;
	(*prepped_data)[pdata_i] = 0;
	while (data_i < len)
	{
		(*prepped_data)[pdata_i] += (((uint64_t)(data[data_i])) <<
				((7 - (data_i % 8)) * 8));
		if (data_i % 8 == 7)
			(*prepped_data)[++pdata_i] = 0;
		data_i++;
	}
	return (pdata_i);
}

int	u8_to_u64_big_end(uint64_t **converted, uint8_t size, uint8_t *data,
		int len)
{
	int	data_i;
	int	converted_i;

	data_i = 0;
	converted_i = 0;
	(*converted)[converted_i] = 0;
	while (data_i < len)
	{
		(*converted)[converted_i] += (((uint64_t)(data[data_i])) <<
				((7 - (data_i % 8)) * 8));
		if (data_i % 8 == 7)
			(*converted)[++converted_i] = 0;
		data_i++;
	}
	return (converted_i);
}

int	u8_to_u32_big_end(uint32_t **converted, uint8_t size, uint8_t *data,
		int len)
{
	int	data_i;
	int	converted_i;

	data_i = 0;
	converted_i = 0;
	(*converted)[converted_i] = 0;
	while (data_i < len)
	{
		(*converted)[converted_i] += (((uint32_t)(data[data_i])) <<
				((3 - (data_i % 4)) * 8));
		if (data_i % 4 == 3)
			(*converted)[++converted_i] = 0;
		data_i++;
	}
	return (converted_i);
}

int	u8_to_u32_little_end(uint32_t **converted, uint8_t size, uint8_t *data,
		int	len)
{
	int	data_i;
	int	converted_i;

	data_i = 0;
	converted_i = 0;
	(*converted)[converted_i] = 0;
	while (data_i < len)
	{
		(*converted)[converted_i] += (((uint32_t)(data[data_i])) <<
				((data_i % 4) * 8));
		if (data_i % 4 == 3)
			(*converted)[++converted_i] = 0;
		data_i++;
	}
	return (converted_i);
}

uint32_t	u32_le_to_u32_be(uint32_t data)
{
	return (((data & BYTE_1_MASK) >> 24) | ((data & BYTE_2_MASK) >> 8) |
			((data & BYTE_3_MASK) << 8) | ((data & BYTE_4_MASK) << 24));
}
