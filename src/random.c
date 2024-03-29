/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   random.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/22 22:08:25 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 22:10:02 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <fcntl.h>
#include <stdlib.h>
#include "ft_ssl.h"
#include "read_data.h"

char	*nrandom(size_t n)
{
	char	*ret;
	int		fd;

	if (!(fd = open("/dev/urandom", O_RDONLY)))
		return (NULL);
	if (!(ret = malloc(sizeof(*ret) * (n + 1))))
		return (NULL);
	if (ft_ssl_read(fd, ret, n) > 0)
		return (ret);
	free(ret);
	return (NULL);
}
