/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   usage.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/06 11:19:26 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/06 11:29:41 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_printf.h"
#include "ft_dstring.h"

int	print_usage(t_ssl_checksum chk)
{
	t_dstring	*s;

	s = ft_dstr_init();
	if (chk.algorithm.type == message_digest)
		ft_printf("usage: ft_ssl %s [-%s] [-s string] [files ...]\n",
				(chk.algorithm.algorithm ? chk.algorithm.name : "command"),
				get_ssl_options(s, chk.algorithm.type)->buf);
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	ft_dstr_free(s);
	return (0);
}
