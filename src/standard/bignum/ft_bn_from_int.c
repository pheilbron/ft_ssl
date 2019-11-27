#include "ft_bignum.h"

t_bignum	*ft_bn_from_u64(t_bignum *result, uint64_t nbr)
{
	int	i;

	result->msb = 0;
	result->overflow = 0;
	result->n[0] = nbr & 0xFFFF;
	if ((result->n[1] = nbr & 0xFFFF0000) == 0)
		result->msb = 1;
	i = 2;
	while (i < BIGNUM_SIZE)
		result->n[i++] = 0;
	return (result);
}
