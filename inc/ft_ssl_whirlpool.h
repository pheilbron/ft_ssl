/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_whirlpool.h                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 21:10:19 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 21:33:43 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_WHIRLPOOL_H
# define FT_SSL_WHIRLPOOL_H

typedef struct	s_whirlpool_chunk
{
	uint64_t	*data;
	uint64_t	len;
	uint64_t	pos;
	uint8_t		w[8][8];
}				t_whirlpool_chunk;

void			ft_ssl_whirlpool(char *data, uint32_t **file_hash);

#endif
