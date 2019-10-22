/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:26:57 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/22 11:42:56 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl_utils.h"

uint64_t	rot_l(uint64_t x, uint8_t shift, uint8_t data_size)
{
	if (shift < data_size)
		return ((x << shift) | (x >> (data_size - shift)));
	return (x);
}

uint64_t	rot_r(uint64_t x, uint8_t shift, uint8_t data_size)
{
	if (shift < data_size)
		return ((x >> shift) | (x << (data_size - shift)));
	return (x);
}

uint64_t	safe_rot_l(uint64_t x, uint8_t shift, uint8_t data_size)
{
	uint64_t	mask;
	uint8_t		i;

	mask = 0;
	i = 0;
	while (i < data_size)
		mask |= 1 << i++;
	if (shift < data_size)
		return (((x << shift) | (x >> (data_size - shift))) & mask);
	return (x);
}

uint64_t	safe_rot_r(uint64_t x, uint8_t shift, uint8_t data_size)
{
	uint64_t	mask;
	uint8_t		i;

	mask = 0;
	i = 0;
	while (i < data_size)
		mask |= 1 << i++;
	if (shift < data_size)
		return (((x >> shift) | (x << (data_size - shift))) & mask);
	return (x);
}
