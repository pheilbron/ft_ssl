/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/20 12:59:54 by pheilbro          #+#    #+#             */
/*   Updated: 2019/12/04 19:19:59 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl_cipher.h"
#include "ft_ssl_des.h"
#include "ft_ssl_options.h"
#include "ft_ssl_utils.h"

t_encryptor_tab_elem	g_des_encryptor_tab[] = {
	{CBC, &ft_ssl_des_cbc_encrypt_block, &ft_ssl_des_cbc_decrypt_block},
	{CFB, &ft_ssl_des_cfb_encrypt_block, &ft_ssl_des_cfb_decrypt_block},
	{CTR, &ft_ssl_des_ctr_encrypt_block, &ft_ssl_des_ctr_decrypt_block},
	{ECB, &ft_ssl_des_ecb_encrypt_block, &ft_ssl_des_ecb_decrypt_block},
	{OFB, &ft_ssl_des_ofb_encrypt_block, &ft_ssl_des_ofb_decrypt_block},
	{PCBC, &ft_ssl_des_pcbc_encrypt_block, &ft_ssl_des_pcbc_decrypt_block},
	{0, NULL, NULL}};

void	(*get_des_block_encryptor(uint16_t flag))(t_des_context *)
{
	int	i;

	i = 0;
	while (g_des_encryptor_tab[i].encode)
	{
		if (g_des_encryptor_tab[i].flag == flag)
			return (g_des_encryptor_tab[i].encode);
		i++;
	}
	return (NULL);
}

void	(*get_des_block_decryptor(uint16_t flag))(t_des_context *)
{
	int	i;

	i = 0;
	while (g_des_encryptor_tab[i].encode)
	{
		if (g_des_encryptor_tab[i].flag == flag)
			return (g_des_encryptor_tab[i].decode);
		i++;
	}
	return (NULL);
}

int	ft_ssl_des(void *data, char **out, uint16_t flag)
{
	t_cipher_context	*c;
	t_des_context		*des;
	int					status;
	void				(*f)(t_des_context *);

	c = (t_cipher_context *)data;
	if (!(f = get_des_block_encryptor(flag)))
		return (c->e.no = INV_BLOCK_CIPHER_MODE);
	if (!(des = init_des_context(c)))
		return ((c->e.no = SYS_ERROR));
	while ((status = set_u64_block(&(des->block), c->in_file->fd, &pad_pkcs7)))
		(*f)(des);
	c->e.no = status != DONE ? SYS_ERROR : 1;
	(*out) = ft_dstr_release(des->out);
	return (c->e.no);
}

int	ft_ssl_des3(void *data, char **out, uint16_t flag)
{
	t_cipher_context	*c;
	t_des_context		des;
	int					status;
	void				(*f)(t_des_context *);
	void				(*f_opp)(t_des_context *);

	c = (t_cipher_context *)data;
	if (!(f = get_des_block_encryptor(flag)))
		return (c->e.no = INV_BLOCK_CIPHER_MODE);
	if (!(f_opp = get_des_block_decryptor(flag)))
		return (c->e.no = INV_BLOCK_CIPHER_MODE);
	if (!init_des_context(&des, c))
		return ((c->e.no = SYS_ERROR));
	while ((status = set_u64_block(&(des.block), c->in_file->fd, &pad_pkcs7)))
	{
		(*f)(&des);
		(*f_opp)(&des);
		(*f)(&des);
	}
	c->e.no = status != DONE ? SYS_ERROR : 1;
	(*out) = ft_dstr_release(des.out);
	return (c->e.no);
}
