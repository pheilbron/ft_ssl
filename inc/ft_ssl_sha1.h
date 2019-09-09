/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_sha1.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/04 12:45:10 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/04 13:23:08 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_SHA1_H
# define FT_SSL_SHA1_H

# include <stdint.h>

# define A 0
# define B 1
# define C 2
# define D 3
# define E 4

typedef struct	s_sha1_chunk
{
	uint32_t	*data;
	uint32_t	len;
	uint32_t	pos;
	uint32_t	s[80];
	uint32_t	hash[5];
	uint32_t	temp[5];
}				t_sha1_chunk;

void	ft_ssl_sha1(char *data, uint32_t **file_hash);

#endif
