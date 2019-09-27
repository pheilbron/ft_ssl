/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_cipher.h                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/27 08:38:57 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/27 14:21:14 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_CIPHER_H
# define FT_SSL_CIPHER_H

typedef struct	s_cipher_context
{
	char	*in_file;
	char	*out_file;
	char	*salt;
	char	*init_vect;
	char	**key;
	char	*password;
}				t_cipher_context;

#endif
