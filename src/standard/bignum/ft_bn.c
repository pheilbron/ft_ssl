#include "ft_bignum.h"

t_bignum	*ft_bn_add(t_bignum *result, t_bignum *a, t_bignum *b)
{
	int			i;
	int			max;
	uint32_t	carry;

	i = 0;
	max = (a->msb > b->msb ? a->msb : b->msb) + 1;
	while (i < max)
	{
		result->overflow += a->n[i] + b->n[i];
		if (result->overflow > UINT32_MAX)
			carry = result->overflow - UINT32_MAX;
		result->n[i] = result->overflow;
		i++;
	}
	result->overflow = 0;
}

t_bignum	*ft_bn_mult(t_bignum *result, t_bignum *a, t_bignum *b)
{
