/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_ctr.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:35:05 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 10:47:50 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"

static void	update_counter(uint64_t *counter)
{
	(*counter)++;
}

void	ft_ssl_des_ctr_encrypt_block(t_des_context *c)
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
	update_counter(&(c->init_vector));
	c->block ^= plaintext;
	ft_dstr_add(c->out, (char *)(c->block), 16);
}

void	ft_ssl_des_ctr_decrypt_block(t_des_context *c)
{
	c->block = 0;
}
