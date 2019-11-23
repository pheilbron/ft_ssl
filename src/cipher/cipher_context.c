/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   cipher_context.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 20:47:54 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 21:30:59 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_ssl_file.h"
#include "ft_ssl_cipher.h"
#include "clean.h"

int					clean_cipher_context(t_cipher_context *c)
{
	if (c->in_file)
		ft_ssl_free_file(c->in_file);
	if (c->out_file)
		ft_ssl_free_file(c->out_file);
	if (c->salt)
		free(c->salt);
	if (c->init_vect)
		free(c->init_vect);
	//free key
	return (1);
}

t_cipher_context	*init_cipher_context(void)
{
	t_cipher_context	*c;

	if (!(c = malloc(sizeof(*c))))
		return (NULL);
	c->in_file = NULL;
	c->out_file = NULL;
	c->init_vect = NULL;
	c->salt = NULL;
	if (!(c->in_file = init_ssl_file()))
	{
		clean_cipher_context(c);
		return (NULL);
	}
	c->in_file->fd = 1;
	if (!(c->out_file = init_ssl_file()))
	{
		clean_cipher_context(c);
		return (NULL);
	}
	c->out_file->fd = 1;
	ft_ssl_new_error(&(c->e), 1, "");
	return (c);
}
