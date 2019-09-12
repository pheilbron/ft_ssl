/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 08:47:48 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/11 18:38:01 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <unistd.h>
#include "read_data.h"
#include "ft_string.h"
#include "ft_math.h"

int	ft_ssl_read(int fd, char *buf, int size)
{
	static struct s_holder	h = {{'\0'}, 0, 0};
	char					read_buf[BUF_SIZE];
	int						total;
	int						ret;

	total = 0;
	ret = 1;
	if ((h.len - h.i) > 0)
	{
		ft_memcpy(buf, h.buf + h.i, (total = ft_min(h.len - h.i, size)));
		h.i = (total > size ? 0 : h.i + total);
	}
	if (total < size)
	{
		if ((ret = read(fd, buf, size)) == size)
			return ((h.len = read(fd, h.buf, BUF_SIZE)) > 0 ? ret : h.len);
		while ((total += ret) < size && ret > 0)
			if ((ret = read(fd, read_buf, size - total)) > 0)
				ft_memcpy(buf + total, read_buf, size - total);
		if (ret > 0)
			h.len = read(fd, h.buf, BUF_SIZE);
	}
	return (ret < 1 ? ret : total);
}
