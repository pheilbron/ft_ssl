/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_des.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/19 09:16:25 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/07 12:51:17 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_DES_H
# define FT_SSL_DES_H

# include <stdint.h>
# include "ft_ssl_cipher.h"
# include "ft_dstring.h"

typedef struct	s_des_context
{
	uint64_t	block;
	t_dstring	*out;
	uint8_t		mode;
	uint8_t		type;
	uint32_t	left;
	uint32_t	right;
	uint64_t	key[3];
	uint64_t	sub_key[16];
	uint64_t	init_vector;
}				t_des_context;

typedef struct	s_encryptor_tab_elem
{
	uint16_t	flag;
	void		(*encode)();
	void		(*decode)();
}				t_encryptor_tab_elem;

extern uint8_t		g_init_permutation_tab[64];
extern uint8_t		g_final_permutation_tab[64];
extern t_tab_elem	g_des_encryptor_tab[6];
extern t_tab_elem	g_des_decryptor_tab[6];

void		ft_ssl_des_cbc_encrypt_block(t_des_context *c);
void		ft_ssl_des_cfb_encrypt_block(t_des_context *c);
void		ft_ssl_des_ctr_encrypt_block(t_des_context *c);
void		ft_ssl_des_ecb_encrypt_block(t_des_context *c);
void		ft_ssl_des_ofb_encrypt_block(t_des_context *c);
void		ft_ssl_des_pcbc_encrypt_block(t_des_context *c);
void		ft_ssl_des_cbc_decrypt_block(t_des_context *c);
void		ft_ssl_des_cfb_decrypt_block(t_des_context *c);
void		ft_ssl_des_ctr_decrypt_block(t_des_context *c);
void		ft_ssl_des_ecb_decrypt_block(t_des_context *c);
void		ft_ssl_des_ofb_decrypt_block(t_des_context *c);
void		ft_ssl_des_pcbc_decrypt_block(t_des_context *c);

int			init_des_context(t_des_context *des, t_cipher_context *c);
void		setup_block(t_des_context *c, int pos, int len, char *s);
void		scramble_des_block(uint64_t *data, uint8_t permutation_tab[64]);
uint64_t	get_substitute_value(int i, uint8_t x);
void		feistel_process(t_des_context *c, int round);
uint64_t	permute_subkey(uint64_t key);
void	init_subkey_tab(t_des_context *c);

#endif
