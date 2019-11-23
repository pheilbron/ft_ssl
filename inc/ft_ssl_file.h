/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_file.h                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:25:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 21:27:22 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_FILE
# define FT_SSL_FILE

# include <stdint.h>
# include "ft_error.h"

typedef struct	s_ssl_file
{
	int			fd;
	char		*reference;
	char		*data;
	uint8_t		flag;
	t_error		e;
}				t_ssl_file;

t_ssl_file		*init_ssl_file(void);
int				clean_ssl_file(t_ssl_file *file);

#endif
