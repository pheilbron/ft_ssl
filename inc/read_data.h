/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   read_data.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/09 10:49:07 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/17 12:26:30 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef READ_DATA_H
# define READ_DATA_H

# define BUF_SIZE 4096

struct	s_holder
{
	char	buf[BUF_SIZE];
	int		i;
	int		len;
};

#endif
