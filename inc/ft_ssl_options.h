/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_options.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:11:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/18 09:45:26 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_OPTIONS_H
# define FT_SSL_OPTIONS_H

# include "ft_ssl.h"

/***************************
**     Shared Options     **
***************************/
# define _P 1
# define _S 2

/***************************
** Message Digest Options **
***************************/
# define _Q 4
# define _R 8
# define IN 16

/** *********************** **
 **      Cipher Options     **
 ** *********************** **/
# define _A 4
# define _D 8
# define _E 16
# define _I 32
# define _K 64
# define _O 128
# define _V 256

# define MD 1
# define CIPHER 2
# define STANDARD 3

# define MD5 1 << 2
# define SHA1 2 << 2
# define SHA224 3 << 2
# define SHA256 4 << 2
# define SHA384 5 << 2
# define SHA512 6 << 2

# define BASE64 1 << 2
# define DES 2 << 2

typedef struct	s_ssl_option
{
	char					op;
	t_ssl_algorithm_type	type;
	uint16_t				flag;
	char					*long_op;
}				t_ssl_option;

extern t_ssl_option	g_options_tab[];

#endif
