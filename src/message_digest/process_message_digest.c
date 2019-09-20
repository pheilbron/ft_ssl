/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_message_digest.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:41:29 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/18 09:46:21 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_queue.h"

void	process_message_digest(t_ssl_context *c)
{
	t_ssl_file	*file;
	char		*hash;

	while (!ft_queue_is_empty(c->data))
	{
		file = (t_ssl_file *)(ft_queue_dequeue(c->data));
		if (file->e.no >= 0)
		{
			if (\\is file)
				(*(c->algorithm.file_f))(file, hash);
			else
				(*(c->algorithm.buffer_f))(file->reference, hash);
			ft_ssl_md_print(hash, c);
			free(hash);
		}
		else
			ft_ssl_print_md_error(file, c->algorithm.name);
		ft_ssl_free_file(file);
	}
	free(c->data);
}
