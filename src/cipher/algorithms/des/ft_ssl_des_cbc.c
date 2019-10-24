/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_cbc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:09:37 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/23 20:03:31 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"

static void	encode_block(t_des_context *c)
{
	int	i;

	i = 0;
	c->block ^= c->init_vector;
	scramble_des_block(&(c->block), g_init_permutation_tab);
	c->left = c->block >> 32;
	c->right = c->block & 0xFFFFFFFF;
	while (i < 16)
		feistel_process(c, i++);
	c->block = ((uint64_t)(c->right) << 32) | (uint64_t)(c->left);
	scramble_des_block(&(c->block), g_final_permutation_tab);
	c->init_vector = c->block;
	ft_dstr_add(c->out, (char *)(c->block), 16);
}

static void	decode_block(t_des_context *c)
{
	c->block = 0;
}

int			ft_ssl_des_cbc(void *data, char **out, uint8_t type)
{
	t_des_context	des;
	int				status;
	t_ssl_context	*c;
	void			(*f)(t_des_context *);

	c = (t_ssl_context *)data;
	if (!init_des_context(&des, (t_cipher_context *)(c->data)))
		return ((c->e.no = SYS_ERROR));
	f = ((c->options & _E) == _E) ? &encode_block : &decode_block;
	while ((status = set_u64_block(&(des.block),
					((t_cipher_context *)c->data)->in_file->fd, &pad_pkcs7)))
		(*f)(&des);
	if (status != DONE)
		c->e.no = SYS_ERROR;
	(*out) = ft_dstr_release(des.out);
	return (1);
}
