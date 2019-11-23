/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_des_utils.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/10 13:23:28 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 22:16:02 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include <stdlib.h>
#include "ft_ssl.h"

#include "ft_ssl_cipher.h"
#include "ft_ssl_des.h"
#include "ft_ssl_utils.h"
#include "ft_dstring.h"

uint8_t	g_expansion_tab[48] = {
	32, 1, 2, 3, 4, 5,
	4, 5, 6, 7, 8, 9,
	8, 9, 10, 11, 12, 13,
	12, 13, 14, 15, 16, 17,
	16, 17, 18, 19, 20, 21,
	20, 21, 22, 23, 24, 25,
	24, 25, 26, 27, 28, 29,
	28, 29, 30, 31, 32, 1};

uint8_t	g_substitution_tab[8][4][16] = {
	{{14, 4, 13, 1, 2, 15, 11, 8, 3, 10, 6, 12, 5, 9, 0, 7},
		{0, 15, 7, 4, 14, 2, 13, 1, 10, 6, 12, 11, 9, 5, 3, 8},
		{4, 1, 14, 8, 13, 6, 2, 11, 15, 12, 9, 7, 3, 10, 5, 0},
		{15, 12, 8, 2, 4, 9, 1, 7, 5, 11, 3, 14, 10, 0, 6, 13}},
	{{15, 1, 8, 14, 6, 11, 3, 4, 9, 7, 2, 13, 12, 0, 5, 10},
		{3, 13, 4, 7, 15, 2, 8, 14, 12, 0, 1, 10, 6, 9, 11, 5},
		{0, 14, 7, 11, 10, 4, 13, 1, 5, 8, 12, 6, 9, 3, 2, 15},
		{13, 8, 10, 1, 3, 15, 4, 2, 11, 6, 7, 12, 0, 5, 14, 9}},
	{{10, 0, 9, 14, 6, 3, 15, 5, 1, 13, 12, 7, 11, 4, 2, 8},
		{13, 7, 0, 9, 3, 4, 6, 10, 2, 8, 5, 14, 12, 11, 15, 1},
		{13, 6, 4, 9, 8, 15, 3, 0, 11, 1, 2, 12, 5, 10, 14, 7},
		{1, 10, 13, 0, 6, 9, 8, 7, 4, 15, 14, 3, 11, 5, 2, 12}},
	{{7, 13, 14, 3, 0, 6, 9, 10, 1, 2, 8, 5, 11, 12, 4, 15},
		{13, 8, 11, 5, 6, 15, 0, 3, 4, 7, 2, 12, 1, 10, 14, 9},
		{10, 6, 9, 0, 12, 11, 7, 13, 15, 1, 3, 14, 5, 2, 8, 4},
		{3, 15, 0, 6, 10, 1, 13, 8, 9, 4, 5, 11, 12, 7, 2, 14}},
	{{2, 12, 4, 1, 7, 10, 11, 6, 8, 5, 3, 15, 13, 0, 14, 9},
		{14, 11, 2, 12, 4, 7, 13, 1, 5, 0, 15, 10, 3, 9, 8, 6},
		{4, 2, 1, 11, 10, 13, 7, 8, 15, 9, 12, 5, 6, 3, 0, 14},
		{11, 8, 12, 7, 1, 14, 2, 13, 6, 15, 0, 9, 10, 4, 5, 3}},
	{{12, 1, 10, 15, 9, 2, 6, 8, 0, 13, 3, 4, 14, 7, 5, 11},
		{10, 15, 4, 2, 7, 12, 9, 5, 6, 1, 13, 14, 0, 11, 3, 8},
		{9, 14, 15, 5, 2, 8, 12, 3, 7, 0, 4, 10, 1, 13, 11, 6},
		{4, 3, 2, 12, 9, 5, 15, 10, 11, 14, 1, 7, 6, 0, 8, 13}},
	{{4, 11, 2, 14, 15, 0, 8, 13, 3, 12, 9, 7, 5, 10, 6, 1},
		{13, 0, 11, 7, 4, 9, 1, 10, 14, 3, 5, 12, 2, 15, 8, 6},
		{1, 4, 11, 13, 12, 3, 7, 14, 10, 15, 6, 8, 0, 5, 9, 2},
		{6, 11, 13, 8, 1, 4, 10, 7, 9, 5, 0, 15, 14, 2, 3, 12}},
	{{13, 2, 8, 4, 6, 15, 11, 1, 10, 9, 3, 14, 5, 0, 12, 7},
		{1, 15, 13, 8, 10, 3, 7, 4, 12, 5, 6, 11, 0, 14, 9, 2},
		{7, 11, 4, 1, 9, 12, 14, 2, 0, 6, 10, 13, 15, 3, 5, 8},
		{2, 1, 14, 7, 4, 10, 8, 13, 15, 12, 9, 0, 3, 5, 6, 11}}};

uint8_t	g_permutation_tab[32] = {
	16, 7, 20, 21, 29, 12, 28, 17,
	1, 15, 23, 26, 5, 18, 31, 10,
	2, 8, 24, 14, 32, 27, 3, 9,
	19, 13, 30, 6, 22, 11, 4, 25};

uint8_t	g_subkey_permutation_tab1[] = {
	57, 49, 41, 33, 25, 17, 9,
	1, 58, 50, 42, 34, 26, 18,
	10, 2, 59, 51, 43, 35, 27,
	19, 11, 3, 60, 52, 44, 36,
	63, 55, 47, 39, 31, 23, 15,
	7, 62, 54, 46, 38, 30, 22,
	14, 6, 61, 53, 45, 37, 29,
	21, 13, 5, 28, 20, 12, 4};

uint8_t	g_subkey_permutation_tab2[] = {
	14, 17, 11, 24, 1, 5,
	3, 28, 15, 6, 21, 10,
	23, 19, 12, 4, 26, 8,
	16, 7, 27, 20, 13, 2,
	41, 52, 31, 37, 47, 55,
	30, 40, 51, 45, 33, 48,
	44, 49, 39, 56, 34, 53,
	46, 42, 50, 36, 29, 32};

int	init_des_context(t_des_context *des, t_cipher_context *c)
{
	int	i;
	
	if (!(des->out = ft_dstr_init()))
		return (0);
	if (!(c->salt))
		c->salt = nrandom(8);
	i = 0;
	while (i < 3)
	{
		if (!(des->key[i] = malloc(sizeof(*(des->key[i])) * 2)))
			return (0);
		i++;
	}
	if (ft_ssl_des_pbkdf(c->password, c->salt, &(des->key),
				&(des->init_vector)) < 0)
		return (0);
	return (1);
}

void	setup_block(t_des_context *c, int pos, int len, char *s)
{
	c->block = 0;
	for (int i = 0; i < 8 && i < len - pos; i++)
		c->block |= ((((uint64_t)(s[i + pos])) & 0xff) << ((7 - i) * 8));
}

void	scramble_des_block(uint64_t *data, uint8_t permutation_tab[64])
{
	int			i;
	uint64_t	out;

	i = 0;
	out = 0;
	while (i < 64)
	{
		out |= (((*data) >> (64 - permutation_tab[i])) & 1) << (63 - i);
		i++;
	}
	(*data) = out;
}

uint64_t	get_substitute_value(int i, uint8_t x)
{
	int	row;

	if ((x & 1) == 0 && ((x >> 5) & 1) == 0)
		row = 0;
	else if ((x & 1) == 0)
		row = 2;
	else if ((x & 1) == 1 && ((x >> 5) & 1) == 0)
		row = 1;
	else
		row = 3;
	return (g_substitution_tab[i][row][(x & 0x1e) >> 1]);
}

void	feistel_process(t_des_context *c, int round)
{
	int 		i;
	uint64_t	out;

	i = -1;
	out = 0;
	while (++i < 48)
		out |= (uint64_t)((c->right >> (32 - g_expansion_tab[i])) & 1) << (63 - i);
	c->block = (out >> 16) ^ c->sub_key[round];
	i = -1;
	out = 0;
	while (++i < 8)
		out |= get_substitute_value(i,
				(c->block >> (42 - (i * 6))) & 0x3f) << (28 - (i * 4));
	c->block = out;
	i = -1;
	out = 0;
	c->block <<= 32;
	while (++i < 32)
		out |= ((c->block >> (64 - g_permutation_tab[i])) & 1) << (63 - i);
	c->block = c->left ^ (out >> 32);
	c->left = c->right;
	c->right = c->block;
}

uint64_t	permute_subkey(uint64_t key)
{
	uint64_t	out;
	int			i;

	i = 0;
	out = 0;
	key <<= 8;
	while (i < 48)
	{
		out |= ((key >> (64 - g_subkey_permutation_tab2[i])) & 1)
			<< (63 - i);
		i++;
	}
	return (out >> 16);
}

void	init_subkey_tab(t_des_context *c)
{
	uint64_t	out;
	uint64_t	temp_tab[2][17];
	int			i;

	i = 0;
	out = 0;
	while (i < 56)
	{
		out |= ((c->key[0] >> (64 - g_subkey_permutation_tab1[i])) & 1)
			<< (63 - i);
		i++;
	}
	c->key[0] = out >> 8;
	temp_tab[0][0] = (c->key[0] & 0xfffffff0000000UL) >> 28;
	temp_tab[1][0] = c->key[0] & 0xfffffffUL;
	i = 1;
	while (i < 17)
	{
		temp_tab[0][i] = safe_rot_l(temp_tab[0][i - 1],
				(i == 1 || i == 2 || i == 9 || i == 16 ? 1 : 2), 28);
		temp_tab[1][i] = safe_rot_l(temp_tab[1][i - 1],
				(i == 1 || i == 2 || i == 9 || i == 16 ? 1 : 2), 28);
		i++;
	}
	i = 1;
	while (i < 17)
	{
		temp_tab[0][i - 1] = ((temp_tab[0][i] << 28) | temp_tab[1][i]);
		i++;
	}
	i = 0;
	while (i < 16)
	{
		c->sub_key[i] = permute_subkey(temp_tab[0][i]);
		i++;
	}
}
