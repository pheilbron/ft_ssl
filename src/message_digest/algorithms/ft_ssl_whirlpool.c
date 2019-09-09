/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_whirlpool.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:33:59 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 21:35:51 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_whirlpool.h"
#include "ft_ssl_message_digest.h"
#include "ft_string.h"

static uint64_t	pad_data(char *data, t_sha512_chunk *chunk)
{
	uint64_t	len;
	uint64_t	i;

	len = ft_strlen(data);
	i = (len * 8) + 257;
	chunk->len = (i + (1024 - (i % 1024))) / 64;
	if ((chunk->data = malloc(sizeof(*chunk->data) * chunk->len)))
	{
		i = ft_ssl_prep_8b_big_end(&(chunk->data), data, len);
		chunk->data[i++] += ULLONG_LEADING_ONE >> ((len % 8) * 8);
		while (i < chunk->len - 2)
			chunk->data[i++] = 0;
		chunk->data[i++] = FIRST_LEN(len) * 8;
		chunk->data[i] = len * 8;
	}
	return (chunk->len);
}


