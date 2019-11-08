/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_pbkdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:46:18 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/08 11:08:07 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include <stdint.h>
#include "ft_ssl_message_digest.h"
#include "ft_ssl_cipher.h"

uint64_t	ft_ssl_des_pbkdf(char *password, char *salt)
{
	int			i;
	char		*key;
	char		*pass_salt;
	uint64_t	ret;

	i = 0;
	ret = 0;
	if (!(pass_salt = malloc(sizeof(*pass_salt) *
					(ft_strlen(password) + ft_strlen(salt)))))

	ft_ssl_md5(password, &key, MD_BUFFER);
	while (i < 8)
	{
		ret |= key[i] << (i * 8);
		i++;
	}
	free(key);
	return (ret);
}
