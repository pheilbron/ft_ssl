/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_options.h                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 19:11:06 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 08:44:11 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_OPTIONS_H
# define FT_SSL_OPTIONS_H

# include "ft_ssl.h"

/**************************
 *     Shared Options     *
 **************************/
# define _P 1
# define _S 2

/**************************
 * Message Digest Options *
 **************************/
# define _Q 4
# define _R 8

/**************************
 *     Cipher Options     *
 **************************/
# define _A 4
# define _D 8
# define _E 16
# define _I 32
# define _K 64
# define _O 128
# define _V 256

typedef struct	s_ssl_option
{
	char						op;
	enum e_ssl_algorithm_type	algorithm_type;
	uint16_t					flag;
}				t_ssl_option;

extern t_ssl_option	g_options_tab[];

#endif
