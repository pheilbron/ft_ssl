/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des_cbc.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:09:37 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/22 12:21:38 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

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

char	*ft_ssl_des_cbc(t_ssl_context *c)
{
	ft_des_context	des;
	int				status;
	void			(*f)();

	if (!init_des_context(&des, c))
		return (NULL);
	f = ((c->flag & _E) == _E) ? &encode_block : &decode_block;
	while ((status = set_u64_bloc))
		(*f)(&des);
	if (status != DONE)
		c->e.no = SYS_ERROR;
	return (ft_dstr_release(des.out));
}
