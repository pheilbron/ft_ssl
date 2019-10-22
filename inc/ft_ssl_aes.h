/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_aes.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:03:12 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/22 13:53:20 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_AES_H
# define FT_SSL_AES_H

# include <stdint.h>
# include "ft_dstring.h"

typedef struct	s_aes_context
{
	uint64_t	block[2];
	t_dstring	*out;
	uint8_t		mode;
	uint64_t	key[4];
	uint8_t		key_size;
	uint64_t	round_key[15][4];
	uint64_t	init_vect;
}				t_des_context;

#endif

