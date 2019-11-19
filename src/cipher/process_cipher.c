/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cipher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:49:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 11:42:59 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	process_cipher(t_ssl_context *c)
{
	char	*cipher_text;

	if (c->in_file->e.no < 0)
		print_non_fatal_error(c, e);
	else if (c->out_file->e.no < 0)
		print_non_fatal_error(c, e);
	else
	{
		write(c->out_file->fd, "Salted__", 8);
		if (c->in_file->fd == 1)
			c->in_file->data = read_in();
		(*(c->algorthm.f))(c->data, &cipher_text, c->options);
		ft_fprintf(c->out_file->fd, "%s", cipher_text);
	}
	clean_cipher_context(c->data);
}
