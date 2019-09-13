/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_input.c                                      :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 14:00:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 14:36:56 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_error.h"
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
//	{base64, "base64", &ft_ssl_base64, &process_cipher},
	{0, NULL, NULL, NULL}
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
