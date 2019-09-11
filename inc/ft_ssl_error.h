/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 09:48:51 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/10 13:45:20 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_ERROR_H
# define FT_SSL_ERROR_H

# define INV_COMMAND -1
# define INV_OPTION -2
# define INV_LONG_OPTION -3
# define INV_FILE -4
# define DIRECTORY -5
# define MISSING_ARG -6
# define SYS_ERROR -7

# define PARSE_ERROR -1
# define NO_DATA_MALLOC -2

typedef struct	s_error
{
	int		no;
	char	*data;
}				t_error;

#endif
