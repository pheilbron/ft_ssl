/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u8_to_u32_be.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:27:26 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 12:27:28 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_utils.h"

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
