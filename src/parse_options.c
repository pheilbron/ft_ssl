/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_options.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:34:53 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/27 14:52:44 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_error.h"

t_ssl_option		g_options_tab[] =
{
    {'a', CIPHER, _A, "base64"},
    {'d', CIPHER, _D, "decrypt"},
    {'e', CIPHER, _E, "encrypt"},
    {'i', CIPHER, _I, "input-file"},
    {'k', CIPHER, _K, "key"},
    {'o', CIPHER, _O, "output-file"},
    {'p', MD, _P, "stdin"},
    {'p', CIPHER, _P, "password"},
    {'q', MD, _Q, "print-quiet"},
    {'r', MD, _R, "print-reverse"},
    {'s', MD, _S, "string"},
    {'s', CIPHER, _S, "salt"},
    {'v', CIPHER, _V, "init-vector"},
    {0, 0, 0, 0}
};

int	set_ssl_option(t_ssl_context *c, char op)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].type.family == c->algorithm.type.family &&
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
		if (g_options_tab[i].type.family == c->algorithm.type.family &&
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
