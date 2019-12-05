/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_subkey.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:58:53 by pheilbro          #+#    #+#             */
/*   Updated: 2019/12/04 19:00:04 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static uint64_t	permute_subkey(uint64_t key)
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
