/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha_utils.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 13:27:30 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/20 13:27:33 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA_UTILS_H
# define FT_SSL_SHA_UTILS_H

# define ONLOAD 1
# define OFFLOAD 2

# define S0 1
# define S1 2

uint32_t	u32_ch(uint32_t a, uint32_t b, uint32_t c);
uint64_t	u64_ch(uint64_t a, uint64_t b, uint64_t c);
uint32_t	u32_maj(uint32_t a, uint32_t b, uint32_t c);
uint64_t	u64_maj(uint64_t a, uint64_t b, uint64_t c);

#endif
