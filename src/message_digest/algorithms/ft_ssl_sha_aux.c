/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha_aux.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 17:26:31 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 17:55:45 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_sha256.h"
#include "ft_ssl_sha512.h"
#include "ft_ssl_message_digest.h"

uint32_t	u32_ch(uint32_t a, uint32_t b, uint32_t c)
{
	return ((a & b) ^ (~a & c));
}

uint64_t	u64_ch(uint64_t a, uint64_t b, uint64_t c)
{
	return ((a & b) ^ (~a & c));
}

uint32_t	u32_maj(uint32_t a, uint32_t b, uint32_t c)
{
	return ((a & b) ^ (a & c) ^ (b & c));
}

uint64_t	u64_maj(uint64_t a, uint64_t b, uint64_t c)
{
	return ((a & b) ^ (a & c) ^ (b & c));
}
