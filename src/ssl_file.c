/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:19:30 by pheilbro          #+#    #+#             */
/*   Updated: 2019/12/04 14:18:09 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_ssl_file.h"
#include "ft_error.h"

t_ssl_file	*init_ssl_file(void)
{
	t_ssl_file	*file;

	if (!(file = malloc(sizeof(*file))))
		return (NULL);
	file->fd = 0;
	file->reference = NULL;
	file->data = NULL;
	file->flag = 0;
	init_ssl_error(&(file->e));
	return (file);
}

int			open_ssl_file(t_ssl_file *file)
{
	if ((file->fd = open(data[i], O_DIRECTORY)) >= 0)
	{
		close(file->fd);
		return (ft_error_new(&(file->e), 2, INV_DIR, file->reference));
	}
	if ((file->fd = open(file->reference, O_RDONLY)) < 0)
		ft_error_new(&(file->e), 2, INV_FILE, file->reference);
	return (file->e.no);
}

int			clean_ssl_file(t_ssl_file *file)
{
	if (file->reference && file->fd > 0)
		free(file->reference);
	if (file->data && file->fd != PARSE_ERROR)
		free(file->data);
	free(file);
	return (1);
}
