#include "ft_ssl_cipher.h"
#include "ft_ssl_des.h"

t_tab_elem	g_des_encryptor_tab[] = {
	{DES_CBC, &ft_ssl_des_cbc_encrypt_block},
	{DES_CFB, &ft_ssl_des_cfb_encrypt_block},
	{DES_CTR, &ft_ssl_des_ctr_encrypt_block},
	{DES_ECB, &ft_ssl_des_ecb_encrypt_block},
	{DES_OFB, &ft_ssl_des_ofb_encrypt_block},
	{DES_PCBC, &ft_ssl_des_pcbc_encrypt_block}}

t_tab_elem	g_des_decryptor_tab[] = {
	{DES_CBC, &ft_ssl_des_cbc_decrypt_block},
	{DES_CFB, &ft_ssl_des_cfb_decrypt_block},
	{DES_CTR, &ft_ssl_des_ctr_decrypt_block},
	{DES_ECB, &ft_ssl_des_ecb_decrypt_block},
	{DES_OFB, &ft_ssl_des_ofb_decrypt_block},
	{DES_PCBC, &ft_ssl_des_pcbc_decrypt_block}}

int	ft_ssl_des(void *data, char **out, uint16_t flag)
{
	t_cipher_context	*c;
	t_des_context		des;
	int					status;
	void				(*f)(t_des_context *);

	c = (t_cipher_context *)data;
	if (!init_des_context(&des, c))
		return ((c->e.no = SYS_ERROR));
	f = get_des_block_encryptor(flag);
	while ((status = set_u64_block(&(des.block), c->in_file->fd, &pad_pkcs7)))
		(*f)(&des);
	c->e.no = status != DONE ? SYS_ERROR : 1;
	(*out) = ft_dstr_release(des.out);
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
	if (!init_des_context(&des, c))
		return ((c->e.no = SYS_ERROR));
	f = get_des_block_encryptor(flag);
	f_opp = get_des_block_decryptor(flag);
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
