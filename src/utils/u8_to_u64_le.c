
#include "ft_ssl_utils.h"

int	u8_to_u64_le(uint8_t *in, uint64_t **out, int len)
{
	int	in_i;
	int	out_i;

	in_i = 0;
	out_i = 0;
	(*out)[out_i] = 0;
	while (in_i < len)
	{
		(*out)[out_i] += (((uint64_t)(in[in_i])) <<
				((in_i % 8) * 8));
		if (in_i % 8 == 7)
			(*out)[++out_i] = 0;
		in_i++;
	}
	return (out_i);
}
