#ifndef
# define FT_BIGNUM_H

# include <stdint.h>
# include <limits.h>

# define BIGNUM_SIZE 20

typedef struct	s_bignum
{
	uint8_t		msb;
	uint32_t	n[BIGNUM_SIZE];
	uint64_t	overflow;
}				t_bignum;

t_bignum	*ft_bn_from_int(t_bignum *result, int nbr);
t_bignum	*ft_bn_from_string(t_bignum *result, char *nbr);

t_bignum	*ft_bn_add(t_bignum *result, t_bignum *a, t_bignum *b);
t_bignum	*ft_bn_sub(t_bignum *result, t_bignum *a, t_bignum *b);
t_bignum	*ft_bn_mult(t_bignum *result, t_bignum *a, t_bignum *b);
t_bignum	*ft_bn_div(t_bignum *result, t_bignum *a, t_bignum *b);
t_bignum	*ft_bn_mod(t_bignum *result, t_bignum *a, t_bignum *b);
t_bignum	*ft_bn_pow(t_bignum *result, t_bignum *base, t_bignum *exp);

#endif
