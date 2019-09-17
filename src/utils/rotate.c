/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rotate.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:26:57 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 12:27:02 by pheilbro         ###   ########.fr       */
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
