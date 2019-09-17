/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cipher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:20:09 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/16 20:15:29 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

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
