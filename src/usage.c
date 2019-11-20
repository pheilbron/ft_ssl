/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:19:26 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 11:41:27 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_printf.h"
#include "ft_dstring.h"

int	print_usage(t_ssl_context c)
{
	t_dstring	*s;

	s = ft_dstr_init();
	if (c.algorithm.type.a.family == MD)
		ft_printf("usage: ft_ssl %s [-%s] [-s string] [files ...]\n",
				(c.algorithm.type.algo ? c.algorithm.name : "command"),
				get_ssl_options(s, c.algorithm.type)->buf);
	else if (c.algorithm.type.family == CIPHER)
		ft_printf("usage: ft_ssl %s [-%s] %s[-i file] [-o file]\n",
				c.algorithm.type.algo ? c.algorithm.name : "command",
				c.algorithm.type.algo != BASE64 ? "" :
				"[-k key] [-p password] [-s salt] [-v init_vector] ",
				get_ssl_options(s, c.algorithm.type)->buf);
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	ft_dstr_free(s);
	return (0);
}
