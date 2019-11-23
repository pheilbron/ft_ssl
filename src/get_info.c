/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:41:21 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/22 19:36:43 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_dstring.h"
#include "ft_string.h"

t_dstring	*get_ssl_options(t_dstring *s, t_ssl_algorithm_type type)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].type.family == type.family &&
				OPTION_ON(g_options_tab[i].flag, ~PAIR_OP_MASK))
				ft_dstr_add(s, &(g_options_tab[i].op), 1);
		i++;
	}
	ft_dstr_add(s, "\0", 1);
	return (s);
}

char		*get_ssl_command(t_ssl_algorithm_type type)
{
	int	i;

	i = 0;
	while (g_algo_tab[i].name)
	{
		if (g_algo_tab[i].type.family == type.family)
			return (g_algo_tab[i].name);
		i++;
	}
	return (NULL);
}

t_dstring	*get_ssl_commands(t_dstring *s, t_ssl_algorithm_type type)
{
	int	i;
	int	count;

	i = 0;
	count = 0;
	ft_dstr_overwrite(s, "\0", 1);
	s->pos = 0;
	while (g_algo_tab[i].name)
	{
		if (g_algo_tab[i].type.family == type.family)
			ft_dstr_addf(s, "%-18s%s", g_algo_tab[i].name,
					count++ % 4 == 3 ? "\n" : "");
		i++;
	}
	return (s);
}
