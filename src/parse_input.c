/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:00:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/23 16:48:31 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_error.h"
#include "ft_ssl_options.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_cipher.h"
#include "ft_string.h"

t_ssl_algorithm	g_algo_tab[] = 
{
	{MD | MD5, "md5", &ft_ssl_md5, &process_message_digest},
	{MD | SHA1, "sha1", &ft_ssl_sha1, &process_message_digest},
	{MD | SHA224, "sha224", &ft_ssl_sha224, &process_message_digest},
	{MD | SHA256, "sha256", &ft_ssl_sha256, &process_message_digest},
	{MD | SHA384, "sha384", &ft_ssl_sha384, &process_message_digest},
	{MD | SHA512, "sha512", &ft_ssl_sha512, &process_message_digest},
	{MD | SHA512_224, "sha512/224", &ft_ssl_sha512_224,
		&process_message_digest},
	{MD | SHA512_256, "sha512/256", &ft_ssl_sha512_256,
		&process_message_digest},
	{CIPHER | BASE64, "base64", &ft_ssl_base64, &process_cipher},
	{CIPHER | DES, "des", &ft_ssl_des_ecb, &process_cipher},
	{CIPHER | DES, "des-cbc", &ft_ssl_des_cbc, &process_cipher},
	{CIPHER | DES, "des-cfb", &ft_ssl_des_cfb, &process_cipher},
	{CIPHER | DES, "des-ctr", &ft_ssl_des_ctr, &process_cipher},
	{CIPHER | DES, "des-ecb", &ft_ssl_des_ecb, &process_cipher},
	{CIPHER | DES, "des-ofb", &ft_ssl_des_ofb, &process_cipher},
	{CIPHER | DES, "des-pcbc", &ft_ssl_des_pcbc, &process_cipher},
//	{CIPHER | AES, "aes128", &ft_ssl_aes128_ecb, &process_cipher},
//	{CIPHER | AES, "aes192", &ft_ssl_aes192_ecb, &process_cipher},
//	{CIPHER | AES, "aes256", &ft_ssl_aes256_ecb, &process_cipher},
//	{CIPHER | AES, "aes128-cbc", &ft_ssl_aes128_cbc, &process_cipher},
//	{CIPHER | AES, "aes128-cfb", &ft_ssl_aes128_cfb, &process_cipher},
//	{CIPHER | AES, "aes128-ctr", &ft_ssl_aes128_ctr, &process_cipher},
//	{CIPHER | AES, "aes128-ecb", &ft_ssl_aes128_ecb, &process_cipher},
//	{CIPHER | AES, "aes128-ofb", &ft_ssl_aes128_ofb, &process_cipher},
//	{CIPHER | AES, "aes128-pcbc", &ft_ssl_aes128_pcbc, &process_cipher},
//	{CIPHER | AES, "aes192-cbc", &ft_ssl_aes192_cbc, &process_cipher},
//	{CIPHER | AES, "aes192-cfb", &ft_ssl_aes192_cfb, &process_cipher},
//	{CIPHER | AES, "aes192-ctr", &ft_ssl_aes192_ctr, &process_cipher},
//	{CIPHER | AES, "aes192-ecb", &ft_ssl_aes192_ecb, &process_cipher},
//	{CIPHER | AES, "aes192-ofb", &ft_ssl_aes192_ofb, &process_cipher},
//	{CIPHER | AES, "aes192-pcbc", &ft_ssl_aes192_pcbc, &process_cipher},
//	{CIPHER | AES, "aes256-cbc", &ft_ssl_aes256_cbc, &process_cipher},
//	{CIPHER | AES, "aes256-cfb", &ft_ssl_aes256_cfb, &process_cipher},
//	{CIPHER | AES, "aes256-ctr", &ft_ssl_aes256_ctr, &process_cipher},
//	{CIPHER | AES, "aes256-ecb", &ft_ssl_aes256_ecb, &process_cipher},
//	{CIPHER | AES, "aes256-ofb", &ft_ssl_aes256_ofb, &process_cipher},
//	{CIPHER | AES, "aes256-pcbc", &ft_ssl_aes256_pcbc, &process_cipher},
	{0, NULL, NULL, NULL, NULL}
};

static int	parse_ssl_command(t_ssl_context *c, char *command)
{
	int	i;

	i = 0;
	while (g_algo_tab[i].name)
	{
		if (ft_strcmp(command, g_algo_tab[i].name) == 0)
		{
			c->algorithm.name = command;
			c->algorithm.type = g_algo_tab[i].type;
			c->algorithm.f = g_algo_tab[i].f;
			c->algorithm.process = g_algo_tab[i].process;
			return (c->e.no = 1);
		}
		i++;
	}
	c->algorithm.algorithm = -1;
	c->e.data = data;
	return (c->e.no = INV_COMMAND);
}

int			parse_input(t_ssl_context *c, char **data, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		return (print_usage(*c));
	ft_ssl_error_init(&(c->e));
	if (parse_ssl_command(c, data[i++]) < 0)
		print_fatal_error(*c);
	else if (c->algorithm->type == message_digest)
		parse_message_digest(c, data, len, &i);
	else if (c->algorithm->type == cipher)
		parse_cipher(c, data, len, &i);
	else if (c->algorithm->type == standard)
		parse_standard(c, data, len, &i);
	else
		print_fatal_error(*c);
	return (c->e.no < 0 ? 0 : 1);
}
