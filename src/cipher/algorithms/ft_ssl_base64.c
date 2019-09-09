/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_base64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 08:47:14 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/09 14:36:28 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_error.h"
#include "ft_dstring.h"

#define SHIFT_1 18
#define SHIFT_2 12
#define SHIFT_3 6

#define MASK_1 (0x3f << S1)
#define MASK_2 (0x3f << S2)
#define MASK_3 (0x3f << S3)
#define MASK_4 0x3f

static char	base64(uint8_t c)
{
	if (c < 26)
		return (c + 'A');
	if (c > 25 && c < 52)
		return (c - 26 + 'a');
	if (c > 51 && c < 62)
		return (c - 52 + '0');
	if (c == 62)
		return ('+');
	if (c == 63)
		return ('\\');
	return (0);
}

static void	set_block(t_dstring *encr_data, char raw_data[48], int len)
{
	int			i;
	uint64_t	trio;

	i = 0;
	while (i < len)
	{
		j = 0;
		trio = 0;
		while (j < 3)
		{
			trio = (trio << 8) + (i + j < len ? raw_data[i + j] : 0);
			j++;
		}
		ft_dstr_addf(encr_data, "%c%c%c%c", base64((trio & MASK_1) >> SHIFT_1),
				base64((trio & MASK_2) >> SHIFT_2),
				i + 1 < len ? base64((trio & MASK_3) >> SHIFT_3) : '=',
				i + 2 < len ? base64(trio & MASK_4) : '=');
		i += 3;
	}
	ft_dstr_add(encr_data, "\n");
}

char		*ft_ssl_base64(t_ssl_file *file)
{
	t_dstring	*encr_data;
	char		raw_data[48];
	int			size;

	if (!(encr_data = ft_dstr_init()))
		return (NULL);
	while ((size = ft_ssl_read(file->fd, raw_data, 48)))
		set_block(encr_data, raw_data, size);
	if (size < 0)
	{
		ft_ssl_new_error(&(file->e), SYS_ERROR, NULL);
		return ((char *)print_fatal_error(file));
	}
	return (ft_dstr_release(chunk.encr_data));
}
