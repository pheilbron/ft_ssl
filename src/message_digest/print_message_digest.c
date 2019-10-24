/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_digest.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:51:20 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/23 14:23:28 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_dstring.h"
#include "ft_string.h"
#include "ft_error.h"
#include "ft_printf.h"

void	ft_ssl_md_print(t_ssl_file *f, char *hash, t_ssl_context *c)
{
	char	*name;

	if ((f->flag & _P) == _P)
		ft_printf("%s%s\n", ((f->flag & IN) != IN) ? f->data : "", hash);
	else if ((c->options & _Q) == _Q)
		ft_printf("%s\n", hash);
	else if ((c->options & _R) == _R)
		ft_printf("%s %s%s%s\n", hash, f->reference ? "" : "\"",
				(f->reference ? f->reference : f->data),
				f->reference ? "" : "\"");
	else
	{
		ft_printf("%s (%s%s%s) = %s\n",
				(name = ft_str_capitalize(c->algorithm.name)) ? name :
				c->algorithm.name, f->reference ? "" : "\"",
				f->reference ? f->reference :
				f->data, f->reference ? "" : "\"", hash);
		if (name)
			free(name);
	}
}

void	ft_ssl_print_md_error(t_ssl_file *file, char *algorithm_name)
{
	t_dstring	*s;

	file->fd = PARSE_ERROR;
	if (!(s = ft_dstr_init()))
		return ;
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
