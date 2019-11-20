
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
    {'a', {CIPHER, DES | AES, 0}, _A_CIPHER, "base64"},
    {'b', {CIPHER, BASE64, 0}, _B_CIPHER, "break"},
    {'d', {CIPHER, ALL_CIPHER, 0}, _D_CIPHER, "decrypt"},
    {'e', {CIPHER, ALL_CIPHER, 0}, _E_CIPHER, "encrypt"},
    {'i', {CIPHER, ALL_CIPHER, 0}, _I_CIPHER, "input-file"},
    {'k', {CIPHER, DES | AES, 0}, _K_CIPHER, "key"},
    {'o', {CIPHER, ALL_CIPHER, 0}, _O_CIPHER, "output-file"},
    {'p', {MD, ALL_MD, 0}, _P_MD, "stdin"},
    {'p', {CIPHER, DES | AES, 0}, _P_CIPHER, "password"},
    {'q', {MD, ALL_MD, 0}, _Q_MD, "print-quiet"},
    {'r', {MD, ALL_MD, 0}, _R_MD, "print-reverse"},
    {'s', {MD, ALL_MD, 0}, _S_MD, "string"},
    {'s', {CIPHER, DES | AES, 0}, _S_CIPHER, "salt"},
    {'v', {CIPHER, DES | AES, 0}, _V_CIPHER, "init-vector"},
    {0, {0, 0, 0}, 0, 0}
};

int	set_ssl_option(t_ssl_context *c, char op)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].op == op &&
				g_options_tab[i].type.family == c->algorithm.type.family &&
				OPTION_ON(g_options_tab[i].type.algo, c->algorithm.type.algo))
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
		if (ft_strcmp(g_options_tab[i].long_op, option) == 0 &&
				g_options_tab[i].type.family == c->algorithm.type.family &&
				OPTION_ON(g_options_tab[i].type.algo, c->algorithm.type.algo))
		{
			c->options |= g_options_tab[i].flag;
			return (c->e.no = (int)g_options_tab[i].flag);
		}
		i++;
	}
	c->e.data = option;
	return (c->e.no = INV_LONG_OPTION);
}
