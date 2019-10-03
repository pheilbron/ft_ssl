/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cipher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:20:09 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/02 17:47:54 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

static int	set_context(t_ssl_context *c, uint16_t op, char **data, int *i)
{
	if (i)
	{
		(*i)++;
		if (op == _I)
			((t_cipher_context *)(c->data))->in_file.reference = data[*i];
		else if (op == _O)
			((t_cipher_context *)(c->data))->out_file.reference = data[*i];
		else if (op == _S)
			((t_cipher_context *)(c->data))->salt = data[*i];
		else if (op == _V)
			((t_cipher_context *)(c->data))->init_vect = data[*i];
		else if (op == _K)
			((t_cipher_context *)(c->data))->key[0] = data[*i];
		else if (op == _P)
			((t_cipher_context *)(c->data))->password = data[*i];
		else
			return (1);
	}
	c->e.data = data[*i];
	return ((c->e.no = MISSING_ARG));
}

static int	parse_cipher_options(t_ssl_context *c, char **data, int len, int *i)
{
	int			data_i;
	uint16_t	new_op;

	while (*i < len && data[*i][0] == '-')
	{
		data_i = 1;
		if (data[*i][data_i] && data[*i][data_i] == '-')
			if ((new_op = set_ssl_long_option(c, data[*i] + ++data_i)) < 0 ||
					set_context(c, new_op, data, *i + 1 < len ? i : NULL) < 0)
				return (c->e.no);
		while (data[*i][data_i])
			if ((new_op = set_ssl_option(c, data[*i][data_i++])) < 0 ||
					(!data[*i][data_i] &&
					set_context(c, new_op, data, *i + 1 < len ? i : NULL) < 0))
				return (c->e.no);
		(*i)++;
	}
	return (c->e.no = 1);
}

static int	init_in_file(t_ssl_context *c)
{
	t_ssl_file	*file;
	struct stat	entry;

	file = ((t_cipher_context *)(c->data))->in_file;
	if (file.reference == '-')
		file.fd = 0;
	if (stat(file.reference, &entry) == 0)
	{
		if (S_ISDIR(entry.st_mode))
			return (ft_ssl_new_error(&(c->e), INV_DIR, file.reference));
		if ((S_IRUSR & entry.st_mode) == S_IRUSR)
			return (ft_ssl_new_error(&(c->e), INV_FILE_OPEN, file.reference));
		if (file.fd = open(file.reference, O_RDONLY) < 0)
			return (ft_ssl_new_error(&(c->e), INV_FILE, file.reference));
	}
	return (c->e.no = SYS_ERROR);
}

static int	init_out_file(t_ssl_context *c)
{
	t_ssl_file	*file;

	file = ((t_cipher_context *)(c->data))->out_file;
	if (file.reference == '-')
		file.fd = 1;
	else if (file.fd = open(file.reference, O_CREAT | O_WRONLY, 0644) < 0)
	{
		if (errno == EISDIR)
			return (ft_ssl_new_error(&(c->e), INV_DIR, file.reference));
		else
			return (ft_ssl_new_error(&(c->e), errno == EACCES ?
						INV_FILE_ACC : INV_FILE, file.reference));
	}
}

void		parse_cipher(t_ssl_context *c, char **data, int len, int *i)
{
	if (len == 1 && parse_cipher_stdin(c) < 0)
		print_fatal_error(*c);
	else if (parse_cipher_options(c, data, len, &i) < 0)
		print_fatal_error(*c);
	else if (((c->flag & _I) == _I && init_in_file(c) < 0) ||
				((c->flag & _O) == _O && init_out_file(c) < 0))
		print_fatal_error(*c);
}
