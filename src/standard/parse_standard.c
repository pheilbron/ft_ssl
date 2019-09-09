/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parse_standard.c                                   :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/05 12:23:00 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 12:32:35 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"

void	parse_standard(t_ssl_context *c, char **data, int len, int *i)
{
	c->e.data = "invalid.";
	c->e.no = (len + data[*i][0]) * -1;
	print_fatal_error(*c);
}
