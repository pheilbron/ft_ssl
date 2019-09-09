/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_error.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/02 09:48:51 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/02 10:12:15 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_ERROR_H
# define FT_SSL_ERROR_H

# define INV_COMMAND -1
# define INV_OPTION -2
# define INV_FILE -3
# define DIRECTORY -4
# define MISSING_ARG -5
# define SYS_ERROR -6

# define PARSE_ERROR -1
# define NO_DATA_MALLOC -2

typedef struct	s_error
{
	int		no;
	char	*data;
}				t_error;

#endif
