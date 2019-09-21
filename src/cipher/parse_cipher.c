/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cipher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:20:09 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/21 15:39:08 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	parse_cipher_options(t_ssl_context *c, char **data, int len, int *i)
{
	int	data_i;

	while (*i < len && data[*i][0] == '-')
	{
		data_i = 1;
		while (data[*i][data_i])
			if (set_ssl_option(chk, data[*i][data_i++], e) < 0)
				return (c->e.no);
		(*i)++;
		if ((c->options & _S) == _S)
		{
			while (((c->options &_S) == _S) &&
					parse_md_string(c, data[i], len, &i) >= 0)
				;
			return (c->e.no = 1);
		}
	}
	return (c->e.no = 1);
}

void	parse_cipher(t_ssl_context *c, char **data, int len, int *i)
{
	if (len == 1)
		c->options |= IN;
	if (len == 1 && parse_md_stdin(c) < 0)
		print_fatal_error(*c);
	else if (parse_cipher_options(c, data, len, &i) < 0)
		print_fatal_error(*c);
	while (i < len && parse_cipher_file(c, data, i) != SYS_ERROR)
		i++;
}
