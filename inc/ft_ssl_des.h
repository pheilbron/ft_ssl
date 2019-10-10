/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 09:16:25 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/03 14:16:22 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

typedef struct	s_des_context
{
	uint64_t	block;
	t_dstring	*out;
	uint8_t		mode;
	uint8_t		type;
	uint32_t	left;
	uint32_t	right;
	uint64_t	key[3];
	uint64_t	round_key[16];
	uint64_t	init_vect;
}				t_des_context;

#endif
