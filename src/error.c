/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:23:22 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 15:44:07 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_error.h"
#include "ft_stdio.h"
#include "ft_printf.h"
#include "ft_dstring.h"

int			print_usage(t_ssl_context c)
{
	t_dstring	*s;

	s = ft_dstr_init();
	if (c.algorithm.type == message_digest)
		ft_printf("usage: ft_ssl %s [-%s] [-s string] [files ...]\n",
				(c.algorithm.algorithm ? c.algorithm.name : "command"),
				get_ssl_options(s, c.algorithm.type)->buf);
	else if (c.algorithm.type == cipher)
		ft_printf("usage: ft_ssl cipher\n");
	else if (c.algorithm.type == standard)
		ft_printf("usage: ft_ssl standard\n");
	else
		ft_printf("usage: ft_ssl command [command opts] [command args]\n");
	ft_dstr_free(s);
	return (0);
}

static void	print_commands(void)
{
	t_dstring		*s;

	if ((s = ft_dstr_init()))
	{
		ft_printf("\nStandard commands:\n%s",
				get_ssl_commands(s, standard)->buf);
		s->pos = 0;
		ft_printf("Message Digest commands:\n%s",
				get_ssl_commands(s, message_digest)->buf);
		s->pos = 0;
		ft_printf("Cipher commands:\n%s",
				get_ssl_commands(s, cipher)->buf);
	}
	ft_dstr_free(s);
}

int			print_fatal_error(t_ssl_context c)
{
	if (c.e.no == INV_COMMAND)
	{
		ft_printf("ft_ssl: '%s' is an invalid command.\n", c.e.data);
		print_commands();
	}
	else if (c.e.no == INV_OPTION)
	{
		ft_printf("ft_ssl: illegal option -- %s\n", c.e.data);
		print_usage(c);
	}
	return (0);
}

void		print_non_fatal_error(t_ssl_hash *hash)
{
	if (hash->e.no < 0)
		ft_printf("%s\n", hash->e.data);
}

t_ssl_hash	*ft_ssl_get_md_error(t_ssl_file *file, char *algorithm_name)
{
	t_ssl_hash	*hash;
	t_dstring	*s;

	if (!(hash = malloc(sizeof(*hash))))
		return (NULL);
	hash->er.no = PARSE_ERROR;
	s = ft_dstr_init();
	if (file->e.no == INV_FILE || file->e.no == DIRECTORY)
		ft_dstr_addf(s, "ft_ssl: %s: %s: %s", algorithm_name,
				file->e.data, (file->e.no == INV_FILE ?
					"No such file or directory" : "Is a directory"));
	else if (file->e.no == MISSING_ARG)
		ft_dstr_addf(s, "ft_ssl: %s: option requires an argument -- s",
				algorithm_name);
	if (file->e.no == INV_FILE || file->e.no == DIRECTORY ||
			file->e.no == MISSING_ARG)
		hash->e.data = ft_dstr_release(s);
	else
		hash->e.no = NO_DATA_MALLOC;
	return (hash);
}

void		ft_ssl_error_init(t_error *e)
{
	e->no = 0;
	e->data = NULL;
}
