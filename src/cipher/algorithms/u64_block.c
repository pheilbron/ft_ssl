/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   u64_block.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:57:29 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/23 11:09:20 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl.h"
#include "ft_ssl_cipher.h"
#include "read_data.h"
#include "ft_error.h"

int	set_u64_block(uint64_t *out, int fd, void (*pad)(char *, char *, int, int))
{
	char	block_data[8];
	int		size;
	int		i;

	if ((size = ft_ssl_read(fd, block_data, 8)) < 0)
		return (SYS_ERROR);
	else if (size == 0)
		return (DONE);
	else if (size < 8)
		pad(block_data, block_data, size, 8);
	i = 0;
	(*out) = 0;
	while (i < 8)
	{
		(*out) |= ((((uint64_t)(block_data[i])) & 0xff) << ((7 - i) * 8));
		i++;
	}
	return (1);
}
