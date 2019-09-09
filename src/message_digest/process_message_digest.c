/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_message_digest.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:41:29 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 15:44:06 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	process_message_digest(t_ssl_context *c)
{
	t_ssl_file	*file;
	t_ssl_hash	*hash;

	while (!ft_queue_is_empty(c->files))
	{
		file = (t_ssl_file *)(ft_queue_dequeue(c->files));
		if (file->e.no >= 0)
			hash = (*(c->algorithm.f))(file);
		else
			hash = ft_ssl_get_md_error(file, c->algorithm.name);
		if (hash)
			ft_queue_enqueue(c->digests, hash);
		ft_ssl_free_file(file);
	}
	free(c->files);
	while (!ft_queue_is_empty(c->digests))
	{
		hash = (t_ssl_hash *)(ft_queue_dequeue(c->digests));
		ft_ssl_md_print(hash, c);
		ft_ssl_free_hash(hash);
	}
	free(c->digests);
}
