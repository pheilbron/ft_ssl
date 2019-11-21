/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u64_le_to_u8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:27:23 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/18 09:13:02 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_utils.h"

int	u64_le_to_u8(uint64_t *in, uint8_t **out, uint8_t len)
{
	uint8_t	i;

	i = 0;
	while (i < len)
	{
		(*out)[i * 8] = in[i] & U32_LE_DIGIT1;
		(*out)[(i * 8) + 1] = (in[i] & U32_LE_DIGIT2) >> U32_LE_SHIFT2;
		(*out)[(i * 8) + 2] = (in[i] & U32_LE_DIGIT3) >> U32_LE_SHIFT3;
		(*out)[(i * 8) + 3] = (in[i] & U32_LE_DIGIT4) >> U32_LE_SHIFT4;
		(*out)[(i * 8) + 4] = (in[i] & U64_LE_DIGIT1) >> U64_LE_SHIFT1;
		(*out)[(i * 8) + 5] = (in[i] & U64_LE_DIGIT2) >> U64_LE_SHIFT2;
		(*out)[(i * 8) + 6] = (in[i] & U64_LE_DIGIT3) >> U64_LE_SHIFT3;
		(*out)[(i * 8) + 7] = (in[i] & U64_LE_DIGIT4) >> U64_LE_SHIFT4;
		i++;
	}
	(*out)[i * 8] = '\0';
	return (len);
}
