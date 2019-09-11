/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:34:53 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/10 13:44:45 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_error.h"

t_ssl_option		g_options_tab[] =
{
    {'a', cipher, _A, "base64"},
    {'d', cipher, _D, "decrypt"},
    {'e', cipher, _E, "encrypt"},
    {'i', cipher, _I, "input-file"},
    {'k', cipher, _K, "key"},
    {'o', cipher, _O, "output-file"},
    {'p', message_digest, _P, "stdin"},
    {'p', cipher, _P, "password"},
    {'q', message_digest, _Q, "print-quiet"},
    {'r', message_digest, _R, "print-reverse"},
    {'s', message_digest, _S, "string"},
    {'s', cipher, _S, "salt"},
    {'v', cipher, _V, "init-vector"},
    {0, 0, 0}
};

int	set_ssl_option(t_ssl_context *c, char op)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].type == c->algorithm.type &&
				g_options_tab[i].op == op)
		{
			chk->options |= g_options_tab[i].flag;
			return (c->e.no = 1);
		}
		i++;
	}
	c->e.data = &op;
	return (c->e.no = INV_OPTION);
}

int	set_ssl_long_option(t_ssl_context *c, char *option)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].type == c->algorithm.type &&
				ft_strcmp(g_options_tab[i].long_op, option) == 0)
		{
			chk->options |= g_options_tab[i].flag;
			return (c->e.no = 1);
		}
		i++;
	}
	c->e.data = option;
	return (c->e.no = INV_LONG_OPTION);
}
