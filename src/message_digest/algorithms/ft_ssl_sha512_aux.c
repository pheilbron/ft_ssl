/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha512_aux.c                                :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 14:30:24 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 17:21:14 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha512.h"
#include "ft_ssl_message_digest.h"

uint64_t	sha512message_schedule_sum(uint64_t message_schedule[80], uint8_t offset,
		uint8_t type)
{
	if (type == S0)
		return (rot_r(message_schedule[offset - 2], 19, 64) ^
				rot_r(message_schedule[offset - 2], 61, 64) ^
				(message_schedule[offset - 2] >> 6));
	if (type == S1)
		return (rot_r(message_schedule[offset - 15], 1, 64) ^
				rot_r(message_schedule[offset - 15], 8, 64) ^
				(message_schedule[offset - 15] >> 7));
	return (0);
}

uint64_t	sha512compression_sum(t_sha512_chunk *c, uint8_t type)
{
	if (type == S0)
		return (rot_r(c->temp[A], 28, 64) ^ rot_r(c->temp[A], 34, 64) ^
				rot_r(c->temp[A], 39, 64));
	if (type == S1)
		return (rot_r(c->temp[E], 14, 64) ^ rot_r(c->temp[E], 18, 64) ^
				rot_r(c->temp[E], 41, 64));
	return (0);
}

uint64_t	sha512choice(t_sha512_chunk *c)
{
	return ((c->temp[E] & c->temp[F]) ^ (~(c->temp[E]) & c->temp[G]));
}

uint64_t	sha512majority(t_sha512_chunk *c)
{
	return ((c->temp[A] & c->temp[B]) ^ (c->temp[A] & c->temp[C]) ^
			(c->temp[B] & c->temp[C]));
}
