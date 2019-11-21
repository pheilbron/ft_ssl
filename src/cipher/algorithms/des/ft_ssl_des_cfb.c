/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_cfb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:24:12 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 10:46:56 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"

void	ft_ssl_des_cfb_encrypt_block(t_des_context *c)
{
	int	i;
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
	c->block ^= plaintext;
	c->init_vector = c->block;
	ft_dstr_add(c->out, (char *)(c->block), 16);
}

void	ft_ssl_des_cfb_decrypt_block(t_des_context *c)
{
	c->block = 0;
}
