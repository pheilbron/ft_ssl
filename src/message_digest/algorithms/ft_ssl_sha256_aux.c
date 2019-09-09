/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha256_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 22:02:22 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 15:44:19 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha256.h"
#include "ft_ssl_message_digest.h"

uint32_t	message_schedule_sum(uint32_t message_schedule[64], uint8_t offset,
		uint8_t type)
{
	if (type == S0)
		return (rot_r(message_schedule[offset - 2], 17, 32) ^
				rot_r(message_schedule[offset - 2], 19, 32) ^
				(message_schedule[offset - 2] >> 10));
	if (type == S1)
		return (rot_r(message_schedule[offset - 15], 7, 32) ^
				rot_r(message_schedule[offset - 15], 18, 32) ^
				(message_schedule[offset - 15] >> 3));
	return (0);
}

uint32_t	compression_sum(t_sha256_chunk *c, uint8_t type)
{
	if (type == S0)
		return (rot_r(c->temp[A], 2, 32) ^ rot_r(c->temp[A], 13, 32) ^
				rot_r(c->temp[A], 22, 32));
	if (type == S1)
		return (rot_r(c->temp[E], 6, 32) ^ rot_r(c->temp[E], 11, 32) ^
				rot_r(c->temp[E], 25, 32));
	return (0);
}

uint32_t	choice(t_sha256_chunk *c)
{
	return ((c->temp[E] & c->temp[F]) ^ ((~c->temp[E] & c->temp[G])));
}

uint32_t	majority(t_sha256_chunk *c)
{
	return ((c->temp[A] & c->temp[B]) ^ (c->temp[A] & c->temp[C]) ^
			(c->temp[B] & c->temp[C]));
}
