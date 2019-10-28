/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des3_cbc.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/28 10:08:37 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/28 10:13:55 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"

int	ft_ssl_des3_cbc(void *data, char **out, uint16_t flag)
{
	t_cipher_context	*c;
	t_des_context		des;
	char				*temp;

	c = (t_cipher_context *)data;
	if (!init_des_context(&des, c))
		return ((c->e.no = SYS_ERROR));
	
	f = ((flag & _E) == _E) ? &encode_block : &decode_block;
	while ((status = set_u64_block(&(des.block), c->in_file->fd, &pad_pkcs7)))
		(*f)(&des);
	c->e.no = status != DONE ? SYS_ERROR : 1;
	(*out) = ft_dstr_release(des.out);
	return (c->e.no);
}
