/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_pbkdf.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 15:46:18 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/11 15:52:51 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

uint64_t	ft_ssl_des_pbkdf(char *password)
{
	int			i;
	char		*key;
	uint64_t	ret;

	i = 0;
	ft_ssl_sha256(password, &key);
	while (i < 8)
	{
		ret |= key[i] << (i * 8);
		i++;
	}
	free(key);
	return (ret);
}
