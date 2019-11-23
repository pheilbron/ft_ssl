/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_cipher.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:20:09 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 21:50:59 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <fcntl.h>
#include <readpassphrase.h>
#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_cipher.h"
#include "ft_error.h"
#include "ft_string.h"
#include "ft_ssl_error.h"
#include "read_data.h"

static int	set_context(t_ssl_context *c, uint16_t op, char **data, int *i)
{
	if (i)
	{
		(*i)++;
		if (op == _I_CIPHER)
			((t_cipher_context *)(c->data))->in_file->reference = data[1];
		else if (op == _O_CIPHER)
			((t_cipher_context *)(c->data))->out_file->reference = data[1];
		else if (op == _S_CIPHER)
			((t_cipher_context *)(c->data))->salt = data[1];
		else if (op == _V_CIPHER)
			((t_cipher_context *)(c->data))->init_vect = data[1];
		else if (op == _K_CIPHER)
			((t_cipher_context *)(c->data))->key[0] = data[1];
		else if (op == _P_CIPHER)
			ft_strncpy(((t_cipher_context *)(c->data))->password, data[1], 256);
		else
			return (1);
	}
	c->e.data = data[0];
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
					set_context(c, new_op, data + *i,
						*i + 1 < len ? i : NULL) < 0)
				return (c->e.no);
		while (data[*i][data_i])
			if ((new_op = set_ssl_option(c, data[*i][data_i++])) < 0 ||
					(!data[*i][data_i] &&
					set_context(c, new_op, data + *i,
						*i + 1 < len ? i : NULL) < 0))
				return (c->e.no);
		(*i)++;
	}
	return (c->e.no = 1);
}

static int	init_file(t_ssl_context *c, t_cipher_context *cipher, uint8_t type)
{
	t_ssl_file	*file;
	struct stat	entry;

	file = type == IN_FILE ? cipher->in_file : cipher->out_file;
	if (file->fd == 1)
	{
		file->reference = ft_strndup("-", 1);
		return (c->e.no = 1);
	}
	if (stat(file->reference, &entry) == 0)
	{
		if (S_ISDIR(entry.st_mode))
			return (ft_ssl_new_error(&(c->e), type == IN_FILE ?
						INV_DIR : INV_DIR_CREATE, file->reference));
		if ((type == IN_FILE) && (S_IRUSR & entry.st_mode) != S_IRUSR)
			return (ft_ssl_new_error(&(c->e), INV_FILE_OPEN, file->reference));
		if ((type == IN_FILE) &&
				(file->fd = open(file->reference, O_RDONLY)) < 0)
			return (ft_ssl_new_error(&(c->e), INV_FILE, file->reference));
		if ((type != IN_FILE) && (S_IWUSR & entry.st_mode) != S_IWUSR)
			return (ft_ssl_new_error(&(c->e), INV_FILE_CREATE, file->reference));
		if ((type != IN_FILE) && (file->fd =
					open(file->reference, O_CREAT | O_WRONLY, 0644)) < 0)
			return (ft_ssl_new_error(&(c->e), INV_FILE, file->reference));
	}
	return (c->e.no = SYS_ERROR);
}

//static int	init_in_file(t_ssl_context *c)
//{
//	t_ssl_file	*file;
//	struct stat	entry;
//
//	file = ((t_cipher_context *)(c->data))->in_file;
//	if (*(file->reference) == '-')
//		file->fd = 0;
//	if (stat(file->reference, &entry) == 0)
//	{
//		if (S_ISDIR(entry.st_mode))
//			return (ft_ssl_new_error(&(c->e), INV_DIR, file->reference));
//		if ((S_IRUSR & entry.st_mode) != S_IRUSR)
//			return (ft_ssl_new_error(&(c->e), INV_FILE_OPEN, file->reference));
//		if ((file->fd = open(file->reference, O_RDONLY)) < 0)
//			return (ft_ssl_new_error(&(c->e), INV_FILE, file->reference));
//	}
//	return (c->e.no = SYS_ERROR);
//}
//
//static int	init_out_file(t_ssl_context *c)
//{
//	t_ssl_file	*file;
//	struct stat	entry;
//
//	file = ((t_cipher_context *)(c->data))->out_file;
//	if (*(file->reference) == '-')
//		file->fd = 1;
//	if (stat(file->reference, &entry) == 0)
//	{
//		if (S_ISDIR(entry.st_mode))
//			return (ft_ssl_new_error(&(c->e), INV_DIR_CREATE, file->reference));
//		if ((S_IWUSR & entry.st_mode) != S_IWUSR)
//			return (ft_ssl_new_error(&(c->e), INV_FILE_CREATE, file->reference));
//		if ((file->fd = open(file->reference, O_CREAT | O_WRONLY, 0644)) < 0)
//			return (ft_ssl_new_error(&(c->e), INV_FILE, file->reference));
//	}
//	return (c->e.no = SYS_ERROR);
//}

//static int	parse_cipher_stdin(t_ssl_context *c)
//{
//	t_ssl_file	*file;
//	t_dstring	*s;
//	char		read_buf[READ_BUF_SIZE];
//	int			size;
//
//	if (!(s = ft_dstr_init()))
//		return (c->e.no = SYS_ERROR);
//	if (!(file = malloc(sizeof(*file))))
//		return (c->e.no = SYS_ERROR);
//	while ((size = read(0, read_buf, READ_BUF_SIZE)) > 0)
//		ft_dstr_add(s, read_buf, size);
//	file->fd = 0;
//	file->reference = ft_dstr_release(s);
//	file->data = file->reference;
//	file->e.no = 1;
//	((t_cipher_context *)(c->data))->in_file = file;
//	return (file->e.no);
//}

static int	parse_cipher_password(t_ssl_context *c, t_cipher_context *cipher)
{
	t_dstring	*s;
	char		v_pass[256];

	if (!(s = ft_dstr_init()))
		return (c->e.no = SYS_ERROR);
	ft_dstr_addf(s, "enter %s encryption password:", c->algorithm.name);
	if (readpassphrase(s->buf, cipher->password, sizeof(cipher->password), 0))
	{
		ft_dstr_insert(s, "Verifying - ", 12, 0);
		if (readpassphrase(s->buf, v_pass, sizeof(v_pass), 0))
		{
			ft_dstr_free(s);
			if (ft_strcmp(cipher->password, v_pass) != 0)
				return (c->e.no = INV_PASS);
			else
				return (c->e.no = 1);
		}
	}
	ft_dstr_free(s);
	return (c->e.no = SYS_ERROR);
}

int			parse_cipher(t_ssl_context *c, char **data, int len, int *i)
{
	t_cipher_context	*cipher;

	if (!(cipher = init_cipher_context()))
	{
		ft_ssl_new_error(&(c->e), SYS_ERROR, "");
		return (print_fatal_error(*c));
	}
	if (parse_cipher_options(c, data, len, i) < 0)
		return (print_fatal_error(*c));
	if (OPTION_ON(_I_CIPHER, c->options) && init_file(c, cipher, IN_FILE) < 0)
		return (print_fatal_error(*c));
	if (OPTION_ON(_O_CIPHER, c->options) && init_file(c, cipher, OUT_FILE) < 0)
		return (print_fatal_error(*c));
	if (parse_cipher_password(c, cipher) < 0)
		return (print_fatal_error(*c));
	c->data = cipher;
	return ((c->e.no = 1));
}
