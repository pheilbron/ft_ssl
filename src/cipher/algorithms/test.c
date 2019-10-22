/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_ecb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/09 19:19:35 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/21 14:11:32 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include <stdio.h>
#include "ft_ssl_des.h"
#include "ft_dstring.h"
#include "ft_printf.h"
#include <string.h>

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
	ft_printf("\tx: %.6b\t-> %.4b\trow: %d col: %d val: %d, %.4b\n", x,
			g_substitution_tab[i][row][(x & 0x1e) >> 1], row, (x & 0x1e) >> 1,
			g_substitution_tab[i][row][(x & 0x1e) >> 1],
			g_substitution_tab[i][row][(x & 0x1e) >> 1]);
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
	ft_printf("expand: %.48llb\n", out >> 16);
	c->block = (out >> 16) ^ c->sub_key[round];
	ft_printf("XOR w/ key: %.48llb\n", c->block);
	i = -1;
	out = 0;
	while (++i < 8)
		out |= get_substitute_value(i,
				(c->block >> (42 - (i * 6))) & 0x3f) << (28 - (i * 4));
	c->block = out;
	ft_printf("post s-block: %.32b\n", c->block);
	i = -1;
	out = 0;
	c->block <<= 32;
	while (++i < 32)
		out |= ((c->block >> (64 - g_permutation_tab[i])) & 1) << (63 - i);
	ft_printf("final p: %.32b\n", out >> 32);
	c->block = c->left ^ (out >> 32);
	c->left = c->right;
	c->right = c->block;
}

static void	encode_block(t_des_context *c)
{
	int			i;

	i = 0;
	ft_printf("M:\t%.64llb\n", c->block);
	scramble_des_block(&(c->block), g_init_permutation_tab);
	ft_printf("IP:\t%.64llb\n", c->block);
	c->left = c->block >> 32;
	c->right = c->block & 0xFFFFFFFF;
	while (i < 16)
	{
		ft_printf("%d left: %.32b\tright: %.32b\n", i, c->left, c->right);
		feistel_process(c, i);
		i++;
	}
	c->block = ((uint64_t)(c->right) << 32) | (uint64_t)(c->left);
	ft_printf("Pre IP-1:\t%.64llb\n", c->block);
	scramble_des_block(&(c->block), g_final_permutation_tab);
	ft_printf("IP-1:\t\t%.64llb\n", c->block);
	ft_printf("\t\t%.16llX\n", c->block);
	ft_dstr_add(c->out, (char *)(c->block), 16);
}

void	setup_block(t_des_context *c, int pos, int len, char *s)
{
	c->block = 0;
	for (int i = 0; i < 8 && i < len - pos; i++)
		c->block |= ((((uint64_t)(s[i + pos])) & 0xff) << ((7 - i) * 8));
}

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

uint64_t    rot_l(uint64_t x, uint8_t shift, uint8_t data_size)
{
	uint64_t	mask;
	uint8_t		i;

	mask = 0;
	i = 0;
	while (i < data_size)
		mask |= 1 << i++;
	if (shift < data_size)
		return (((x << shift) | (x >> (data_size - shift))) & mask);
	return (x);
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
	ft_printf("K:\t%.64llb\n", c->key[0]);
	c->key[0] = out >> 8;
	ft_printf("K+:\t%.64llb\n", c->key[0]);
	temp_tab[0][0] = (c->key[0] & 0xfffffff0000000UL) >> 28;
	temp_tab[1][0] = c->key[0] & 0xfffffffUL;
	for (int j = 1; j < 17; j++)
	{
		temp_tab[0][j] = rot_l(temp_tab[0][j - 1],
				(j == 1 || j == 2 || j == 9 || j == 16 ? 1 : 2), 28);
		temp_tab[1][j] = rot_l(temp_tab[1][j - 1],
				(j == 1 || j == 2 || j == 9 || j == 16 ? 1 : 2), 28);
	}
	for (int j = 1; j < 17; j++)
		ft_printf("\t%.28b\t%.28b\n", temp_tab[0][j], temp_tab[1][j]);
	for (int j = 1; j < 17; j++)
	{
		temp_tab[0][j - 1] = ((temp_tab[0][j] << 28) | temp_tab[1][j]);
		ft_printf("\t%.64llb\n", temp_tab[0][j - 1]);
	}
	for (int j = 0; j < 16; j++)
	{
		c->sub_key[j] = permute_subkey(temp_tab[0][j]);
	}
}

void	print_subkey_tab(t_des_context c)
{
	for (int i = 0; i < 16; i++)
	{
		ft_printf("%.48llb\n", c.sub_key[i]);
	}
	ft_printf("\n");
}

int	main(void)
{
	t_des_context	des;

	des.key[0] = 0x133457799BBCDFF1ULL;
	int	pos = 0;
	char	*s = "\x1\x23\x45\x67\x89\xAB\xCD\xEF";
	ft_printf("MESSAGE: ");
	for (int i = 0; i < 8; i++)
		ft_printf("%.8b ", s[i]);
	ft_printf("\n");
	int	len = 8;
	if (!(des.out = ft_dstr_init()))
		return (0);
	init_subkey_tab(&des);
	print_subkey_tab(des);
	while (pos < len)
	{
		setup_block(&des, pos, len, s);
		encode_block(&des);
		pos += 8;
	}
	ft_printf("answer: %s\n", ft_dstr_release(des.out));
	return (0);
}
