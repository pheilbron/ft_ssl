/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   clean.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/01 15:46:23 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 14:29:48 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_ssl_error.h"

int	ft_ssl_free_error(t_error *e)
{
	int	error_no;

	error_no = e->no;
	if (e->no == INV_COMMAND)
		free(e->data);
//	free(e);
	return (error_no);
}

int	ft_ssl_free_hash(t_ssl_hash *hash)
{
	int	error_no;

	error_no = hash->e.no;
	free(data);
	if (errno < 0)
		free(hash->e.data);
	return (errno);
}
