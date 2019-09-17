/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_digest.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:51:20 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 14:29:34 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_dstring.h"
#include "ft_printf.h"

void	ft_ssl_md_print(t_ssl_file *f, t_ssl_context *c)
{
	char	*p_hash;
	char	*name;

	if ((p_hash = u32_to_u8_be(f->hash, c->algorithm.hash_len)))
	{
		if ((f->flag & _P) == _P)
			ft_printf("%s%s\n", ((f->flag & IN) != IN) ? f->data : "", p_hash);
		else if ((c->options & _Q) == _Q)
			ft_printf("%s\n", p_hash);
		else if ((c->options & _R) == _R)
			ft_printf("%s %s%s%s\n", p_hash, f->name ? "" : "\"",
					(f->name ? f->name : f->data), f->name ? "" : "\"");
		else
		{
			ft_printf("%s (%s%s%s) = %s\n",
					(name = ft_str_capitalize(c->algorithm.name)) ? name :
					c->algorithm.name, f->name ? "" : "\"", f->name ? f->name :
					f->data, f->name ? "" : "\"", p_hash);
			if (name)
				free(name);
		}
		free(p_hash);
	}
	else
		ft_printf("\n");
}
