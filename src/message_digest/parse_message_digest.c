/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_message_digest.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 11:34:36 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/18 09:44:32 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <unistd.h>
#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_ssl_error.h"
#include "ft_string.h"

#define READ_BUF_SIZE 4096

static int	parse_md_stdin(t_ssl_context *c)
{
	t_ssl_file	*file;
	t_dstring	*s;
	char		read_buf[READ_BUF_SIZE];
	int			size;

	if (!(file = malloc(sizeof(*file))))
		return (c->e.no = SYS_ERROR);
	s = ft_dstr_init();
	while ((size = read(0, read_buf, READ_BUF_SIZE)) > 0)
		ft_dstr_add(s, read_buf, size);
	file->fd = 0;
	file->reference = ft_dstr_release(s);
	file->data = file->reference;
	file->e.no = 1;
	file->flag = c->options | _P;
	ft_queue_push(c->data, file);
	return (file->e.no);
}

static int	parse_md_file(t_ssl_context *c, char **data, int i)
{
	t_ssl_file	*file;

	if (!(file = malloc(sizeof(*file))))
		return (c->e.no = SYS_ERROR);
	if ((file->fd = open(data[i], O_DIRECTORY)))
	{
		close(file->fd);
		ft_ssl_new_error(&(file->e), DIRECTORY, data[i]);
	}
	else if ((file->fd = open(data[i], O_RDONLY)) < 0)
		ft_ssl_new_error(&(file->e), INV_FILE, data[i]);
	else
	{
		file->reference = data[i];
		file->e.no = 1;
	}
	file->flag = c->options & ~_P & ~_S;
	ft_queue_enqueue(c->data, file);
	return (file->e.no);
}

static int	parse_md_string(t_ssl_context *c, char **data, int len, int *i)
{
	t_ssl_file	*file;

	if (*i >= len)
		return (c->e.no = MISSING_ARG);
	if (!(file = malloc(sizeof(*file))))
		return (c->e.no = SYS_ERROR);
	file->fd = 0;
	file->reference = data[(*i)++];
	file->data = file->reference;
	file->flag = (c->options & ~_P) | _S;
	file->e.no = 1;
	ft_queue_enqueue(c->data, file);
	if ((*i < len && ft_strcmp("-s", data[*i]) != 0 &&
				ft_strcmp("--string", data[*i]) != 0) || *i >= len)
		c->options &= ~_S;
	else if (*i < len)
		(*i)++;
	return (file->e.no);
}

static int	parse_md_options(t_ssl_context *c, char **data, int len, int *i)
{
	int	data_i;

	while (*i < len && data[*i][0] == '-')
	{
		data_i = 1;
		if (data[*i][data_i] && data[*i][data_i] == '-')
			if (set_ssl_long_option(c, data[*i] + ++data_i) < 0)
				return (c->e.no);
		while (data[*i][data_i])
			if (set_ssl_option(c, data[*i][data_i++]) < 0)
				return (c->e.no);
		(*i)++;
		if ((c->options & _S) == _S)
		{
			while (((c->options & _S) == _S) &&
					parse_md_string(c, &(data[*i]), len, i) >= 0)
				;
			return (c->e.no = 1);
		}
	}
	return (c->e.no = 1);
}

void		parse_message_digest(t_ssl_context *c, char **data, int len,
		int *i)
{
	if (len == 1)
		c->options |= IN;
	if (len == 1 && parse_md_stdin(c) < 0)
		print_fatal_error(*c);
	else if (parse_md_options(c, data, len, i) < 0)
		print_fatal_error(*c);
	else if ((c->options & _P) == _P)
		parse_md_stdin(c);
	while (*i < len && parse_md_file(c, data, *i) != SYS_ERROR)
		(*i)++;
}
