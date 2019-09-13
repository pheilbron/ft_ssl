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
	t_dstring	*s;

	file->fd = PARSE_ERROR;
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
		ft_printf("%s\n", s->buf);
	ft_dstr_free(s);
}

void		ft_ssl_error_init(t_error *e)
{
	e->no = 0;
	e->data = NULL;
}

int			ft_ssl_new_error(t_error *e, int no, char *data)
{
	e->no = no;
	e->data = data;
	return (no);
}
