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

// DES PASSWORD : MD5(PASSWORD || SALT); [:16] -> key, [16:] -> IV
// DES3 PASSWORD : key = md5(pass || salt) + md5(md5(pass || salt) || pass || salt)[:16], IV = second half of second calculation

int	ft_ssl_des_pbkdf(char *password, char *salt, uint64_t *key[3], uint64_t *iv)
{
	char	*pass_salt;
	char	*key_iv;
	size_t	pass_len;

	pass_len = ft_strlen(password);
	if (!(pass_salt = malloc(sizeof(*pass_salt) *
					(pass_len + ft_strlen(salt)))))
		return (SYS_ERROR);
	ft_strcpy(pass_salt, password);
	ft_strcpy(pass_salt + pass_len, salt);
	ft_ssl_md5(pass_salt, &key_iv, MD_BUFFER);
	u8_to_u64_be(key_iv, &key, 16);
	u8_to_u64_be(key_iv, &iv, 16);
	return (1);
}

int	ft_ssl_des3_pbkdf(char *password, char *salt, uint64_t *key[3], uint64_t *iv)
{
	char	*pass_salt;
	char	*key_iv;
	size_t	pass_len;

	pass_len = ft_strlen(password);
	if (!(pass_salt = malloc(sizeof(*pass_salt) *
					(pass_len + ft_strlen(salt)))))
		return (SYS_ERROR);
	ft_strcpy(pass_salt, password);
	ft_strcpy(pass_salt + pass_len, salt);
	ft_ssl_md5(pass_salt, &key_iv, MD_BUFFER);
	u8_to_u64_be(key_iv, &key, 48);
	u8_to_u64_be(key_iv, &iv, 16);
	return (1);
}
