/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   des_context.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/12/04 18:53:42 by pheilbro          #+#    #+#             */
/*   Updated: 2019/12/04 18:57:29 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	init_des_context(t_des_context *des, t_cipher_context *c)
{
	if (!(des = malloc(sizeof(*des))))
		return (0);
	des->out = NULL;
	des->block = 0;
	des->mode = 0;
	des->type = 0;
	des->left = 0;
	des->right = 0;
	if (!(des->out = ft_dstr_init()))
		return (0);
	if (!(c->salt))
		c->salt = nrandom(8);
	if (ft_ssl_des_pbkdf(c->password, c->salt, &(des->key),
				&(des->init_vector)) < 0)
		return (0);
	return (1);
}
