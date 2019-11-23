/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ssl_file.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 21:19:30 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 21:33:32 by pheilbro         ###   ########.fr       */
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

int			clean_ssl_file(t_ssl_file *file)
{
	if (file->reference && file->fd > 0)
		free(file->reference);
	if (file->data && file->fd != PARSE_ERROR)
		free(file->data);
	free(file);
	return (1);
}