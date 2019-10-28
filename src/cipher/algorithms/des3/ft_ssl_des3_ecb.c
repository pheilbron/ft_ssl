/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_ecb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:19:35 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 10:46:10 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"

uint8_t	g_init_permutation_tab[64] = {
	58, 50, 42, 34, 26, 18, 10, 2,
	60, 52, 44, 36, 28, 20, 12, 4,
	62, 54, 46, 38, 30, 22, 14, 6,
	64, 56, 48, 40, 32, 24, 16, 8,
	57, 49, 41, 33, 25, 17, 9, 1,
	59, 51, 43, 35, 27, 19, 11, 3,
	61, 53, 45, 37, 29, 21, 13, 5,
	63, 55, 47, 39, 31, 23, 15, 7};

uint8_t g_final_permutation_tab[64] = {
	40, 8, 48, 16, 56, 24, 64, 32,
	39, 7, 47, 15, 55, 23, 63, 31,
	38, 6, 46, 14, 54, 22, 62, 30,
	37, 5, 45, 13, 53, 21, 61, 29,
	36, 4, 44, 12, 52, 20, 60, 28,
	35, 3, 43, 11, 51, 19, 59, 27,
	34, 2, 42, 10, 50, 18, 58, 26,
	33, 1, 41, 9, 49, 17, 57, 25};

static void	encode_block(t_des_context *c)
{
	int	i;

	i = 0;
	scramble_des_block(&(c->block), g_init_permutation_tab);
	c->left = c->block >> 32;
	c->right = c->block & 0xFFFFFFFF;
	while (i < 16)
		feistel_process(c, i++);
	c->block = ((uint64_t)(c->right) << 32) | (uint64_t)(c->left);
	scramble_des_block(&(c->block), g_final_permutation_tab);
	ft_dstr_add(c->out, (char *)(c->block), 16);
}

static void	decode_block(t_des_context *c)
{
	c->block = 0;
}

int			ft_ssl_des_ecb(void *data, char **out, uint64_t flag)
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
