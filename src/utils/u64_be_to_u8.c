/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u64_be_to_u8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:27:17 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 15:34:59 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_utils.h"

int	u64_be_to_u8(uint64_t *in, uint8_t **out, uint8_t len)
{
	uint8_t	i;

	i = 0;
	while (i < len)
	{
		(*out)[(i * 16) + 0] = HEX[(in[i] & U64_BE_DIGIT1L) >> U64_BE_SHIFT1L];
		(*out)[(i * 16) + 1] = HEX[(in[i] & U64_BE_DIGIT1R) >> U64_BE_SHIFT1R];
		(*out)[(i * 16) + 2] = HEX[(in[i] & U64_BE_DIGIT2L) >> U64_BE_SHIFT2L];
		(*out)[(i * 16) + 3] = HEX[(in[i] & U64_BE_DIGIT2R) >> U64_BE_SHIFT2R];
		(*out)[(i * 16) + 4] = HEX[(in[i] & U64_BE_DIGIT3L) >> U64_BE_SHIFT3L];
		(*out)[(i * 16) + 5] = HEX[(in[i] & U64_BE_DIGIT3R) >> U64_BE_SHIFT3R];
		(*out)[(i * 16) + 6] = HEX[(in[i] & U64_BE_DIGIT4L) >> U64_BE_SHIFT4L];
		(*out)[(i * 16) + 7] = HEX[(in[i] & U64_BE_DIGIT4R) >> U64_BE_SHIFT4R];
		(*out)[(i * 16) + 8] = HEX[(in[i] & U32_BE_DIGIT1L) >> U32_BE_SHIFT1L];
		(*out)[(i * 16) + 9] = HEX[(in[i] & U32_BE_DIGIT1R) >> U32_BE_SHIFT1R];
		(*out)[(i * 16) + 10] = HEX[(in[i] & U32_BE_DIGIT2L) >> U32_BE_SHIFT2L];
		(*out)[(i * 16) + 11] = HEX[(in[i] & U32_BE_DIGIT2R) >> U32_BE_SHIFT2R];
		(*out)[(i * 16) + 12] = HEX[(in[i] & U32_BE_DIGIT3L) >> U32_BE_SHIFT3L];
		(*out)[(i * 16) + 13] = HEX[(in[i] & U32_BE_DIGIT3R) >> U32_BE_SHIFT3R];
		(*out)[(i * 16) + 14] = HEX[(in[i] & U32_BE_DIGIT4L) >> U32_BE_SHIFT4L];
		(*out)[(i * 16) + 15] = HEX[(in[i] & U32_BE_DIGIT4R) >> U32_BE_SHIFT4R];
		i++;
	}
	(*out)[i * 16] = '\0';
	return (len);
}
