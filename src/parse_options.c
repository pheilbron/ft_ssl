
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
#include "ft_string.h"

t_ssl_option		g_options_tab[] =
{
    {'a', {CIPHER | DES}, _A, "base64"},
    {'b', {CIPHER | BASE64}, _B, "break"},
    {'d', {CIPHER | BASE64 | DES}, _D, "decrypt"},
    {'e', {CIPHER | BASE64 | DES}, _E, "encrypt"},
    {'i', {CIPHER | BASE64 | DES}, _I, "input-file"},
    {'k', {CIPHER | DES}, _K, "key"},
    {'o', {CIPHER | BASE64 | DES}, _O, "output-file"},
    {'p', {MD | MD_ALL}, _P, "stdin"},
    {'p', {CIPHER | DES}, _P, "password"},
    {'q', {MD | MD_ALL}, _Q, "print-quiet"},
    {'r', {MD | MD_ALL}, _R, "print-reverse"},
    {'s', {MD | MD_ALL}, _S, "string"},
    {'s', {CIPHER | DES}, _S, "salt"},
    {'v', {CIPHER | DES}, _V, "init-vector"},
    {0, {0}, 0, 0}
};

int	set_ssl_option(t_ssl_context *c, char op)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].type.algorithm.family ==
				c->algorithm.type.algorithm.family &&
				g_options_tab[i].type.algorithm.algo ==
				(c->algorithm.type.algorithm.algo &
				   g_options_tab[i].type.algorithm.algo) &&
				g_options_tab[i].op == op)
		{
			c->options |= g_options_tab[i].flag;
			return (c->e.no = (int)g_options_tab[i].flag);
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
		if (g_options_tab[i].type.algorithm.family ==
				c->algorithm.type.algorithm.family &&
				g_options_tab[i].type.algorithm.algo ==
				(c->algorithm.type.algorithm.algo &
				   g_options_tab[i].type.algorithm.algo) &&
				ft_strcmp(g_options_tab[i].long_op, option) == 0)
		{
			c->options |= g_options_tab[i].flag;
			return (c->e.no = (int)g_options_tab[i].flag);
		}
		i++;
	}
	c->e.data = option;
	return (c->e.no = INV_LONG_OPTION);
}
