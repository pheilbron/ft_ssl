/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_cipher.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/23 16:49:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/20 13:08:48 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_cipher.h"
#include "ft_printf.h"

void	print_cipher_error(t_ssl_context *c, t_error e)
{
	ft_printf("Error %s %d\n", c->algorithm.name, e.no);
}

void	process_cipher(t_ssl_context *ctx)
{
	char				*cipher_text;
	t_cipher_context	*c;

	c = ctx->data;
	if (c->in_file->e.no < 0)
		print_cipher_error(ctx, c->in_file->e);
	else if (c->out_file->e.no < 0)
		print_cipher_error(ctx, c->out_file->e);
	else
	{
		write(c->out_file->fd, "Salted__", 8);
//		if (c->in_file->fd == 1)
//			c->in_file->data = read_in();
		(*(ctx->algorithm.f))(c, &cipher_text, ctx->algorithm.type.mode);
		ft_fprintf(c->out_file->fd, "%s", cipher_text);
	}
//	clean_cipher_context(c);
}
