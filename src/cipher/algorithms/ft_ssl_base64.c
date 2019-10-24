/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_base64.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 08:47:14 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/24 11:55:39 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_error.h"
#include "ft_ssl_options.h"
#include "read_data.h"
#include "ft_dstring.h"

#define SHIFT_1 18
#define SHIFT_2 12
#define SHIFT_3 6

#define MASK_1 (0x3f << SHIFT_1)
#define MASK_2 (0x3f << SHIFT_2)
#define MASK_3 (0x3f << SHIFT_3)
#define MASK_4 0x3f

#define D_SHIFT_1 16
#define D_SHIFT_2 8

#define D_MASK_1 0xff0000
#define D_MASK_2 0xff00
#define D_MASK_3 0xff

static char	char_to_base64(uint8_t c)
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

static char	base64_to_char(uint8_t c)
{
	if (c >= 'A' && c <= 'Z')
		return (c - 'A');
	if (c >= 'a' && c <= 'z')
		return (c - 'a' + 26);
	if (c >= '0' && c <= '9')
		return (c - '0' + 52);
	if (c == '+')
		return (62);
	if (c == '\\')
		return (63);
	return (0);
}

static void	encrypt_block(t_dstring *data_out, char *raw_data, int len)
{
	uint32_t	trio;
	int			i;
	int			j;

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
		ft_dstr_addf(data_out, "%c%c%c%c",
				char_to_base64((trio & MASK_1) >> SHIFT_1),
				char_to_base64((trio & MASK_2) >> SHIFT_2),
				i + 1 < len ? char_to_base64((trio & MASK_3) >> SHIFT_3) : '=',
				i + 2 < len ? char_to_base64(trio & MASK_4) : '=');
		i += 3;
	}
	ft_dstr_add(data_out, "\n", 1);
}

static void	decrypt_block(t_dstring *data_out, char *raw_data, int len)
{
	uint32_t	trio;
	int			i;
	int			j;

	i = 0;
	while (i < len)
	{
		trio = 0;
		j = 0;
		while (i < len && j < 4)
		{
			while (!base64_to_char(raw_data[i]))
				i++;
			trio = (trio << 6) + (i < len ? raw_data[i] : 0);
			j++;
			i++;
		}
		ft_dstr_addf(data_out, "%c%c%c",
				j > 0 ? base64_to_char((trio & D_MASK_1) >> D_SHIFT_1) : '\0',
				j > 1 ? base64_to_char((trio & D_MASK_2) >> D_SHIFT_2) : '\0',
				j > 2 ? base64_to_char(trio & D_MASK_3) : '\0');
	}
}

int			ft_ssl_base64(void *data, char **out, uint16_t type)
{
	t_dstring	*data_out;
	char		*raw_data;
	int			block_size;
	int			read_size;
	t_ssl_file	*file;

	file = (t_ssl_file *)data;
	if (!(data_out = ft_dstr_init()))
		return (SYS_ERROR);
	block_size = (type & _D) == _D ? 65 : 48;
	if (!(raw_data = malloc(sizeof(*raw_data) * (1 + block_size))))
		return (SYS_ERROR + 0 * ft_dstr_free(data_out));
	while ((read_size = ft_ssl_read(file->fd, raw_data, block_size)))
		block_size == 48 ? encrypt_block(data_out, raw_data, read_size) :
			decrypt_block(data_out, raw_data, read_size);
	if (read_size < 0)
	{
		ft_ssl_new_error(&(file->e), SYS_ERROR, NULL);
		ft_error_print_std_message("ft_ssl", file->e);
		return (SYS_ERROR);
	}
	(*out) = ft_dstr_release(data_out);
	return (1);
}
