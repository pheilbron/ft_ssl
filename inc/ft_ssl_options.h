/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_options.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:11:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/20 13:58:51 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_OPTIONS_H
# define FT_SSL_OPTIONS_H

# include "ft_ssl.h"

# define OPTION_ON(spec, generic) (((spec) & (generic)) == (spec))

# define _S_MD 1UL

# define _P_MD 1UL << 8
# define _Q_MD 1UL << 9
# define _R_MD 1UL << 10
# define IN 1UL << 11

# define _I_CIPHER 1UL
# define _K_CIPHER 1UL << 1
# define _O_CIPHER 1UL << 2
# define _P_CIPHER 1UL << 3
# define _S_CIPHER 1UL << 4
# define _V_CIPHER 1UL << 5

# define _A_CIPHER 1UL << 8
# define _B_CIPHER 1UL << 9
# define _D_CIPHER 1UL << 10
# define _E_CIPHER 1UL << 11

# define PAIR_OP_MASK 0xFF

# define MD 1
# define CIPHER 2
# define STANDARD 3

# define CBC 1
# define CFB 2
# define CTR 3
# define ECB 4
# define OFB 5
# define PCBC 6

# define MD5 1
# define SHA1 1 << 1
# define SHA224 1 << 2
# define SHA256 1 << 3
# define SHA384 1 << 4
# define SHA512 1 << 5
# define SHA512_224 1 << 6
# define SHA512_256 1 << 7
# define WHIRLPOOL 1 << 8
# define ALL_MD 0x1FF

# define BASE64 1
# define DES 1 << 1
# define DES3 1 << 2
# define AES128 1 << 3
# define AES192 1 << 4
# define AES256 1 << 5
# define ALL_DES 0x6
# define ALL_AES 0x70
# define ALL_CIPHER 0x3F

typedef struct	s_ssl_option
{
	char					op;
	t_ssl_algorithm_type	type;
	uint16_t				flag;
	char					*long_op;
}				t_ssl_option;

extern t_ssl_option	g_options_tab[];

#endif
