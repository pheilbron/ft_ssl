/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/08/07 19:38:59 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 14:29:22 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdlib.h>
#include "ft_ssl.h"
#include "ft_queue.h"

static t_ssl_context	*init_context(void)
{
	t_ssl_context	*ret;

	if (!(ret = malloc(sizeof(*ret))))
		return (NULL);
	if (!(ret->files = ft_queue_init()))
	{
		free(ret);
		return (NULL);
	}
	if (!(ret->digests = ft_queue_init()))
	{
		free(ret);
		return (NULL);
	}
	return (ret);
}

int						main(int ac, char **av)
{
	t_ssl_context	*c;

	c = init_context();
	if (parse_input(c, av + 1, ac - 1))
		(*(c->algorithm.process))(c);
	free(c);
	return (0);
}
