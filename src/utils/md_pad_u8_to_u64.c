/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   md_pad_u8_to_u64.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:26:53 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 15:25:35 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include <limits.h>
#include "ft_ssl.h"
#include "ft_ssl_utils.h"
#include "ft_string.h"

#define U64_LE_PAD_LEN1(x) (x * 8)
#define U64_LE_PAD_LEN2(x) (x / (ULLONG_MAX / 8) * 8)
#define U64_BE_PAD_LEN1(x) (x / (ULLONG_MAX / 8) * 8)
#define U64_BE_PAD_LEN2(x) (x * 8)

uint64_t	md_pad_u8_to_u64(char *in, uint64_t **out, uint8_t type)
{
	uint64_t	len;
	uint64_t	out_len;
	uint64_t	i;

	len = ft_strlen(in);
	i = (len * 8) + 129;
	out_len = (i + (1024 - (i % 1024))) / 64;
	if ((*out = malloc(sizeof(**out) * out_len)))
	{
		if (type == LITTLE_END)
			i = u8_to_u64_le((uint8_t *)in, out, len);
		else
			i = u8_to_u64_be((uint8_t *)in, out, len);
		(*out)[i++] += (type == LE ? U64_LE_PAD_ONE(len) : U64_BE_PAD_ONE(len));
		while (i < out_len - 2)
			(*out)[i++] = 0;
		(*out)[i++] = (type == LE ? U64_LE_PAD_LEN1(len) : U64_BE_PAD_LEN1(len));
		(*out)[i] = (type == LE ? U64_LE_PAD_LEN2(len) : U64_BE_PAD_LEN2(len));
	}
	return (out_len);
}
