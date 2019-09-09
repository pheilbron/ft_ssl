/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:34:53 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 07:50:58 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_error.h"

t_ssl_option		g_options_tab[] =
{
    {'a', cipher, _A},
    {'d', cipher, _D},
    {'e', cipher, _E},
    {'i', cipher, _I},
    {'k', cipher, _K},
    {'o', cipher, _O},
    {'p', message_digest, _P},
    {'p', cipher, _P},
    {'q', message_digest, _Q},
    {'r', message_digest, _R},
    {'s', message_digest, _S},
    {'s', cipher, _S},
    {'v', cipher, _V},
    {0, 0, 0}
};

int	set_ssl_option(t_ssl_context *c, char op)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].op == op &&
				g_options_tab[i].type == c->algorithm.type)
		{
			chk->options |= g_options_tab[i].flag;
			return (c->e.no = 1);
		}
		i++;
	}
	return (c->e.no = INV_OPTION);
}
