/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u32_be_to_u8.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:27:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/18 09:10:30 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_utils.h"

int	u32_be_to_u8(uint32_t *in, uint8_t **out, uint8_t len)
{
	uint8_t	i;

	i = 0;
	while (i < len)
	{
		(*out)[i * 4] = (in[i] & U32_BE_DIGIT1) >> U32_BE_SHIFT1;
		(*out)[(i * 4) + 1] = (in[i] & U32_BE_DIGIT2) >> U32_BE_SHIFT2;
		(*out)[(i * 4) + 2] = (in[i] & U32_BE_DIGIT3) >> U32_BE_SHIFT3;
		(*out)[(i * 4) + 3] = in[i] & U32_BE_DIGIT4;
		i++;
	}
	(*out)[i * 4] = '\0';
	return (len);
}
