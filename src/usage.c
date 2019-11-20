/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:19:26 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/20 12:33:32 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_error.h"
#include "ft_printf.h"
#include "ft_dstring.h"

int	print_usage(t_ssl_context c)
{
	t_dstring	*s;

	s = ft_dstr_init();
	if (c.e.no == INV_OPTION)
	{
		if (c.algorithm.type.family == MD)
			ft_printf("usage: ft_ssl %s [-%s] [-s string] [files ...]\n",
					(c.algorithm.type.algo ? c.algorithm.name : "command"),
					get_ssl_options(s, c.algorithm.type)->buf);
		else if (c.algorithm.type.family == CIPHER)
			ft_printf("usage: ft_ssl %s [-%s] %s[-i file] [-o file]\n",
					c.algorithm.type.algo ? c.algorithm.name : "command",
					get_ssl_options(s, c.algorithm.type)->buf,
					c.algorithm.type.algo != BASE64 ? "" :
					"[-k key] [-p password] [-s salt] [-v init_vector] ");
	}
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	ft_dstr_free(s);
	return (0);
}
