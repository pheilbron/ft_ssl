/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_cbc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:09:37 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 11:56:32 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"

void	ft_ssl_des_cbc_encrypt_block(t_des_context *c)
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

void	ft_ssl_des_cbc_decrypt_block(t_des_context *c)
{
	int	i;

	i = 15;
	c->init_vector = c->block;
	scramble_des_block(&(c->block), g_final_permutation_tab);
	c->left = c->block >> 32;
	c->right = c->block & 0xFFFFFFFF;
	while (i >= 0)
		feistel_process(c, i--);
	c->block = ((uint64_t)(c->right) << 32) | (uint64_t)(c->left);
	scramble_des_block(&(c->block), g_init_permutation_tab);
	c->block ^= c->init_vector;
	ft_dstr_add(c->out, (char *)(c->block), 16);
}
