/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_md_block.h                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:48:29 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 16:31:29 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_MD_BLOCK_H
# define FT_SSL_MD_BLOCK_H

typedef struct	s_u32_md_block
{
	uint32_t	*data;
	uint8_t		size;
	uint32_t	*bit_len;
	uint8_t		bit_len_size;
	short		padding;
}				t_u32_md_block;

typedef struct	s_u64_md_block
{
	uint64_t	*data;
	uint8_t		size;
	uint64_t	*bit_len;
	uint8_t		bit_len_size;
	short		padding;
}				t_u64_md_block;

#endif
