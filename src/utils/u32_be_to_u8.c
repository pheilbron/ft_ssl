/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u32_be_to_u8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:27:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/21 12:00:45 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_utils.h"

int	u32_be_to_u8(uint32_t *in, uint8_t **out, uint8_t len)
{
	uint8_t	i;

	i = 0;
	while (i < len)
	{
		(*out)[(i * 8) + 0] = HEX[(in[i] & U32_BE_DIGIT1L) >> U32_BE_SHIFT1L];
		(*out)[(i * 8) + 1] = HEX[(in[i] & U32_BE_DIGIT1R) >> U32_BE_SHIFT1R];
		(*out)[(i * 8) + 2] = HEX[(in[i] & U32_BE_DIGIT2L) >> U32_BE_SHIFT2L];
		(*out)[(i * 8) + 3] = HEX[(in[i] & U32_BE_DIGIT2R) >> U32_BE_SHIFT2R];
		(*out)[(i * 8) + 4] = HEX[(in[i] & U32_BE_DIGIT3L) >> U32_BE_SHIFT3L];
		(*out)[(i * 8) + 5] = HEX[(in[i] & U32_BE_DIGIT3R) >> U32_BE_SHIFT3R];
		(*out)[(i * 8) + 6] = HEX[(in[i] & U32_BE_DIGIT4L) >> U32_BE_SHIFT4L];
		(*out)[(i * 8) + 7] = HEX[(in[i] & U32_BE_DIGIT4R) >> U32_BE_SHIFT4R];
		i++;
	}
	(*out)[i * 8] = '\0';
	return (len);
}
