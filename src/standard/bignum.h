/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   bignum.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 13:11:11 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/07 13:53:11 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef BIGNUM_H
# define BIGNUM_H

typedef struct	s_bignum_mini
{
	uint64_t	left;
	uint64_t	right;
}				t_bignum_mini;

typedef struct	t_bignum
{
	t_vector	*
