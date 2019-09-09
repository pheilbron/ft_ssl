/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   get_info.c                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/07/25 15:41:21 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/05 13:25:12 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "ft_ssl.h"
#include "ft_ssl_options.h"
#include "ft_dstring.h"
#include "ft_string.h"

t_dstring	*get_ssl_options(t_dstring *s, enum e_ssl_algorithm_type type)
{
	int	i;

	i = 0;
	while (g_options_tab[i].op)
	{
		if (g_options_tab[i].algorithm_type == type &&
				(g_options_tab[i].algorithm_type != message_digest &&
					g_options_tab[i].op != 's'))
				ft_dstr_add(s, &(g_options_tab[i].op), 1);
		i++;
	}
	ft_dstr_add(s, "\0", 1);
	return (s);
}

char		*get_ssl_command(enum e_ssl_algorithm type)
{
	int	i;

	i = 0;
	while (g_algo_tab[i].algorithm)
	{
		if (g_algo_tab[i].algorithm == type)
			return (g_algo_tab[i].name);
		i++;
	}
	return (NULL);
}

t_dstring	*get_ssl_commands(t_dstring *s, enum e_ssl_algorithm_type type)
{
	int	i;

	i = 0;
	ft_dstr_overwrite(s, "\0", 1);
	s->pos = 0;
	while (g_algo_tab[i].algorithm)
	{
		if (g_algo_tab[i].type == type)
			ft_dstr_addf(s, "%s\n", g_algo_tab[i].name);
		i++;
	}
	return (s);
}
