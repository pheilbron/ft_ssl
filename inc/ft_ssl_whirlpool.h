/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_whirlpool.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:10:19 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/20 12:26:28 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_WHIRLPOOL_H
# define FT_SSL_WHIRLPOOL_H

typedef struct	s_whirlpool_chunk
{
	t_u64_md_block	block;
	uint64_t		state[8];
	uint64_t		temp[8];
	uint64_t		key[8];
}				t_whirlpool_chunk;

#endif
