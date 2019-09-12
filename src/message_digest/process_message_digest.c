/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   process_message_digest.c                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 13:41:29 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/11 18:49:39 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	process_message_digest(t_ssl_context *c)
{
	t_ssl_file	*file;

	while (!ft_queue_is_empty(c->files))
	{
		file = (t_ssl_file *)(ft_queue_dequeue(c->files));
		if (file->e.no >= 0)
			(*(c->algorithm.f))(file); //first choose if buffer or file
			ft_ssl_md_print(hash, c);
			//then print right away
		else
			ft_ssl_get_md_error(file, c->algorithm.name); //print error
			//immediately
		ft_ssl_free_file(file);
	}
	free(c->files);
}
