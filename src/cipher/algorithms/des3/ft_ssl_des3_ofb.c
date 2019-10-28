/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_ofb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:30:18 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 10:48:41 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"

static void	encode_block(t_des_context *c)
{
	int			i;
	uint64_t	plaintext;

	i = 0;
	plaintext = c->block;
	c->block ^= c->init_vector;
	scramble_des_block(&(c->block), g_init_permutation_tab);
	c->left = c->block >> 32;
	c->right = c->block & 0xFFFFFFFF;
	while (i < 16)
		feistel_process(c, i++);
	c->block = ((uint64_t)(c->right) << 32) | (uint64_t)(c->left);
	scramble_des_block(&(c->block), g_final_permutation_tab);
	c->init_vector = c->block;
	c->block ^= plaintext;
	ft_dstr_add(c->out, (char *)(c->block), 16);
}

static void	decode_block(t_des_context *c)
{
	c->block = 0;
}

int			ft_ssl_des_ofb(void *data, char **out, uint16_t flag)
{
	t_cipher_context	*c;
	t_des_context		des;
	int					status;
	void				(*f)(t_des_context *);

	c = (t_ssl_context *)data;
	if (!init_des_context(&des, c))
		return ((c->e.no = SYS_ERROR));
	f = ((flag & _E) == _E) ? &encode_block : &decode_block;
	while ((status = set_u64_block(&(des.block), c->in_file->fd, &pad_pkcs7)))
		(*f)(&des);
	c->e.no = status != DONE ? SYS_ERROR : 1;
	(*out) = ft_dstr_release(des.out);
	return (c->e.no);
}
