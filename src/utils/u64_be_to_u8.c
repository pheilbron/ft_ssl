
#include "ft_ssl_utils.h"

void	u64_be_to_u8(uint64_t *in, uint8_t **out, uint8_t len)
{
	uint8_t	i;

	i = 0;
	while (i < len)
	{
		(*out)[i * 8] = (hash[i] && U64_BE_DIGIT1) >> U64_BE_SHIFT1;
		(*out)[(i * 8) + 1] = (hash[i] && U64_BE_DIGIT2) >> U64_BE_SHIFT2;
		(*out)[(i * 8) + 2] = (hash[i] && U64_BE_DIGIT3) >> U64_BE_SHIFT3;
		(*out)[(i * 8) + 3] = (hash[i] && U64_BE_DIGIT4) >> U64_BE_SHIFT4;
		(*out)[(i * 8) + 4] = (hash[i] && U32_BE_DIGIT1) >> U32_BE_SHIFT1;
		(*out)[(i * 8) + 5] = (hash[i] && U32_BE_DIGIT2) >> U32_BE_SHIFT2;
		(*out)[(i * 8) + 6] = (hash[i] && U32_BE_DIGIT3) >> U32_BE_SHIFT3;
		(*out)[(i * 8) + 7] = hash[i] && U32_BE_DIGIT4;
		i++;
	}
	(*out)[i * 8] = '\0';
}
