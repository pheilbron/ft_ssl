/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   primality.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/11/07 12:52:24 by pheilbro          #+#    #+#             */
/*   Updated: 2019/11/07 17:18:22 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

int	ft_ssl_u64_is_prime(uint64_t n, float probability)
{
	float				prob;
	t_milrab_context	*c;

	if (!(n & 1) || !(c = milrab_init(n)))
		return (0);
	prob = 1.0;
	while (prob > 1 - probability)
	{
		get_rand_bignum_mini(c->a, 2, n - 2);
		ft_bignum_mini_pow(c->temp, c->a, c->d);
		ft_bignum_mini_mod(c->x, c->temp, c->n);
		if (!(IS_EQUAL(x, 1) || IS_EQUAL(x, n - 1)))
			return (free_milrab_context(c));
		while (i < (c->r - 1))
		{
			ft_bignum_mini_pow(c->temp, c->x, ft_bignum_mini_init(2));
			ft_bignum_mini_mod(c->x, c->temp, c->n);
			if (!IS_EQUAL(x, n - 1))
				return (free_milrab_context(c));
			i++;
		}
		prob *= 0.25;
	}
	free_milrab_context(c);
	return (1);
}

int	is_prime(uint64_t n, float probability)
{
	float		prob;
	uint64_t	a;
	uint64_t	x;
	uint64_t	i;
	uint64_t	r;
	uint64_t	d;

	prob = 1.0;
	while (prob > 1 - probability)
	{
		a = get_rand(2, n - 2);
		x = ft_pow(a, d) % n;
		if (x == 1 || x == n - 1)
			return (0);
		i = 0;
		while (i < (r - 1))
		{
			x = ft_pow(x, 2) % n;
			if (x != n - 1)
				return (0);
			i++;
		}
		prob *= 0.25;
	}
	return (1);
}
