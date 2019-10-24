/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_pbkdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:46:18 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/23 16:32:47 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl_message_digest.h"
#include "ft_ssl_cipher.h"

uint64_t	ft_ssl_des_pbkdf(char *password)
{
	int			i;
	char		*key;
	uint64_t	ret;

	i = 0;
	ret = 0;
	ft_ssl_sha256(password, &key, MD_BUFFER);
	while (i < 8)
	{
		ret |= key[i] << (i * 8);
		i++;
	}
	free(key);
	return (ret);
}
