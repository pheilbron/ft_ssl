/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_aes_key_utils.c                                 :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/10/22 13:36:00 by pheilbro          #+#    #+#             */
/*   Updated: 2019/10/22 13:53:19 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

void	rotate_word(uint32_t word)
{
	return ((word << 8) | (word >> 24));
}

void	sub_word(uint32_t word)
{
	

void	init_key_schedule(t_aes_context *c)
{
	int	n;
	int	r;

