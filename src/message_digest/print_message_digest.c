/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   print_message_digest.c                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:51:20 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 15:44:04 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_dstring.h"
#include "ft_printf.h"

void	ft_ssl_md_print(t_ssl_hash *hash, t_ssl_context *c, int first)
{
	char	*print_hash;
	uint8_t	i;
	char	*name;

	if (hash->e.no < 0)
		print_non_fatal_error(hash);
	else if ((print_hash = u32_to_u8_be(hash->data, hash->len)))
	{
		i = 0;
		if (first && (options & _P) == _P)
			ft_printf("%s\n%s\n", hash->file_ref, print_hash);
		else if ((options & _Q) == _Q)
			ft_printf("%s\n", print_hash);
		else if ((options & _R) == _R)
			ft_printf("%s %s\n", print_hash, hash->file_ref);
		else
			ft_printf("%s (%s) = %s\n",
					(name = ft_str_capitalize(c->algorithm.name)) ?
					name : c->algorithm.name, hash->file_ref, print_hash);
		if (name)
			free(name);
		free(print_hash);
	}
	else
		ft_printf("\n");
}
