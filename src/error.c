/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   error.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/29 11:23:22 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/20 11:31:03 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_error.h"
#include "ft_ssl_options.h"
#include "ft_stdio.h"
#include "ft_printf.h"
#include "ft_dstring.h"

t_error	g_error_tab[] =
{
	{INV_COMMAND, "'%s' is an invalid command.", ""},
	{INV_OPTION, "illegal option -- %.1s", ""},
	{INV_LONG_OPTION, "illegal option -- %s", ""},
	{INV_FILE, "%s: No such file or directory", ""},
	{INV_DIR, "%s: Is a directory", ""},
	{INV_PASS, "Verify failure\nbad password read", ""},
	{MISSING_ARG, "%s: option requires an argument -- %s", ""},
	{INV_ACC_OPEN, "Unable to open '%s': No such file or directory", ""},
	{INV_FILE_OPEN, "Unable to open '%s': Permission denied", ""},
	{INV_FILE_CREATE, "Unable to create '%s': Permission denied", ""},
	{INV_DIR_CREATE, "Unable to create '%s': Is a directory", ""},
	{INV_DES_KEY, "bad decrypt", ""},
	{0, "", ""}
};

void	print_commands(void)
{
	t_dstring	*s;

	if ((s = ft_dstr_init()))
	{
		ft_printf("\nStandard commands:\n%s", get_ssl_commands(s,
					(t_ssl_algorithm_type){ .family = STANDARD })->buf);
		s->pos = 0;
		ft_printf("Message Digest commands:\n%s", get_ssl_commands(s,
					(t_ssl_algorithm_type){ .family = MD })->buf);
		s->pos = 0;
		ft_printf("Cipher commands:\n%s", get_ssl_commands(s,
					(t_ssl_algorithm_type){ .family = CIPHER })->buf);
	}
	ft_dstr_free(s);
}

int			print_fatal_error(t_ssl_context c)
{
	ft_error_print_std_message("ft_ssl", c.e);
	if (c.e.no == INV_COMMAND || c.e.no == INV_OPTION)
		print_usage(c);
	return (0);
}

void		print_non_fatal_error(t_ssl_file *file, char *algorithm_name)
{
	t_dstring	*s;

	file->fd = PARSE_ERROR;
	s = ft_dstr_init();
	if (file->e.no == INV_FILE || file->e.no == INV_DIR)
		ft_dstr_addf(s, "ft_ssl: %s: %s: %s", algorithm_name,
				file->e.data, (file->e.no == INV_FILE ?
					"No such file or directory" : "Is a directory"));
	else if (file->e.no == MISSING_ARG)
		ft_dstr_addf(s, "ft_ssl: %s: option requires an argument -- s",
				algorithm_name);
	if (file->e.no == INV_FILE || file->e.no == INV_DIR ||
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
