/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_aes_ecb.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 12:56:57 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/22 13:35:46 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

static void	encrypt_block(t_aes_context *c)
{


char	*ft_ssl_aes_ecb(t_ssl_context *c)
{
	ft_aes_context	aes;
	int				status;
	void			(*f)();

	if (!init_aes_context(&des, c))
		return (NULL);
	f = ((c->flag & _E) == _E) ? &encode_block : &decode_block;
	while ((status = set_u64_bloc))
		(*f)(&aes);
	if (status != DONE)
		c->e.no = SYS_ERROR;
	return (ft_dstr_release(aes.out));
}
