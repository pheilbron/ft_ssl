/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:00:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/20 13:37:19 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_error.h"
#include "ft_ssl_options.h"
#include "ft_ssl_message_digest.h"
#include "ft_ssl_cipher.h"
#include "ft_error.h"
#include "ft_string.h"

t_ssl_algorithm	g_algo_tab[] =
{
	{{MD, MD5, 0}, "md5", &ft_ssl_md5, &process_message_digest},
	{{MD, SHA1, 0}, "sha1", &ft_ssl_sha1, &process_message_digest},
	{{MD, SHA224, 0}, "sha224", &ft_ssl_sha224, &process_message_digest},
	{{MD, SHA256, 0}, "sha256", &ft_ssl_sha256, &process_message_digest},
	{{MD, SHA384, 0}, "sha384", &ft_ssl_sha384, &process_message_digest},
	{{MD, SHA512, 0}, "sha512", &ft_ssl_sha512, &process_message_digest},
	{{MD, SHA512_224, 0}, "sha512/224", &ft_ssl_sha512_224,
		&process_message_digest},
	{{MD, SHA512_256, 0}, "sha512/256", &ft_ssl_sha512_256,
		&process_message_digest},
	{{CIPHER, BASE64, 0}, "base64", &ft_ssl_base64, &process_cipher},
	{{CIPHER, DES, CBC}, "des", &ft_ssl_des, &process_cipher},
	{{CIPHER, DES, CBC}, "des-cbc", &ft_ssl_des, &process_cipher},
	{{CIPHER, DES, CFB}, "des-cfb", &ft_ssl_des, &process_cipher},
	{{CIPHER, DES, CTR}, "des-ctr", &ft_ssl_des, &process_cipher},
	{{CIPHER, DES, ECB}, "des-ecb", &ft_ssl_des, &process_cipher},
	{{CIPHER, DES, OFB}, "des-ofb", &ft_ssl_des, &process_cipher},
	{{CIPHER, DES, PCBC}, "des-pcbc", &ft_ssl_des, &process_cipher},
	{{CIPHER, DES3, CBC}, "des3", &ft_ssl_des3, &process_cipher},
	{{CIPHER, DES3, CBC}, "des3-cbc", &ft_ssl_des3, &process_cipher},
	{{CIPHER, DES3, CFB}, "des3-cfb", &ft_ssl_des3, &process_cipher},
	{{CIPHER, DES3, CTR}, "des3-ctr", &ft_ssl_des3, &process_cipher},
	{{CIPHER, DES3, ECB}, "des3-ecb", &ft_ssl_des3, &process_cipher},
	{{CIPHER, DES3, OFB}, "des3-ofb", &ft_ssl_des3, &process_cipher},
	{{CIPHER, DES3, PCBC}, "des3-pcbc", &ft_ssl_des3, &process_cipher},
//	{{CIPHER, AES128, CBC}, "aes128", &ft_ssl_aes128, &process_cipher},
//	{{CIPHER, AES128, CBC}, "aes128-cbc", &ft_ssl_aes128, &process_cipher},
//	{{CIPHER, AES128, CFB}, "aes128-cfb", &ft_ssl_aes128, &process_cipher},
//	{{CIPHER, AES128, CTR}, "aes128-ctr", &ft_ssl_aes128, &process_cipher},
//	{{CIPHER, AES128, ECB}, "aes128-ecb", &ft_ssl_aes128, &process_cipher},
//	{{CIPHER, AES128, OFB}, "aes128-ofb", &ft_ssl_aes128, &process_cipher},
//	{{CIPHER, AES128, PCBC}, "aes128-pcbc", &ft_ssl_aes128, &process_cipher},
//	{{CIPHER, AES192, CBC}, "aes192", &ft_ssl_aes192, &process_cipher},
//	{{CIPHER, AES192, CBC}, "aes192-cbc", &ft_ssl_aes192, &process_cipher},
//	{{CIPHER, AES192, CFB}, "aes192-cfb", &ft_ssl_aes192, &process_cipher},
//	{{CIPHER, AES192, CTR}, "aes192-ctr", &ft_ssl_aes192, &process_cipher},
//	{{CIPHER, AES192, ECB}, "aes192-ecb", &ft_ssl_aes192, &process_cipher},
//	{{CIPHER, AES192, OFB}, "aes192-ofb", &ft_ssl_aes192, &process_cipher},
//	{{CIPHER, AES192, PCBC}, "aes192-pcbc", &ft_ssl_aes192, &process_cipher},
//	{{CIPHER, AES256, CBC}, "aes256", &ft_ssl_aes256, &process_cipher},
//	{{CIPHER, AES256, CBC}, "aes256-cbc", &ft_ssl_aes256, &process_cipher},
//	{{CIPHER, AES256, CFB}, "aes256-cfb", &ft_ssl_aes256, &process_cipher},
//	{{CIPHER, AES256, CTR}, "aes256-ctr", &ft_ssl_aes256, &process_cipher},
//	{{CIPHER, AES256, ECB}, "aes256-ecb", &ft_ssl_aes256, &process_cipher},
//	{{CIPHER, AES256, OFB}, "aes256-ofb", &ft_ssl_aes256, &process_cipher},
//	{{CIPHER, AES256, PCBC}, "aes256-pcbc", &ft_ssl_aes256, &process_cipher},
	{{0, 0, 0}, NULL, NULL, NULL}
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
	c->algorithm.type = (t_ssl_algorithm_type){0, 0, 0};
	ft_error_new(&(c->e), 2, INV_COMMAND, command);
	return (c->e.no);
}

int			parse_input(t_ssl_context *c, char **data, int len)
{
	int	i;

	i = 0;
	if (len == 0)
		return (print_usage(*c));
	ft_error_new(&(c->e), 0);
	if (parse_ssl_command(c, data[i++]) < 0)
		print_fatal_error(*c);
	else if (c->algorithm.type.family == MD)
		parse_message_digest(c, data, len, &i);
	else if (c->algorithm.type.family == CIPHER)
		parse_cipher(c, data, len, &i);
	else if (c->algorithm.type.family == STANDARD)
		parse_standard(c, data, len, &i);
	else
		print_fatal_error(*c);
	return (c->e.no < 0 ? 0 : 1);
}
