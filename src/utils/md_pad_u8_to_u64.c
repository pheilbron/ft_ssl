
#include <stdint.h>
#include "ft_ssl_utils.h"

#define U64_LE_DIGIT1(x) (x * 8)
#define U64_LE_DIGIT2(x) (x / (1ULL / 8) * 8)
#define U64_BE_DIGIT1(x) (x / (1ULL / 8) * 8)
#define U64_BE_DIGIT2(x) (x * 8)

#define U64_LE_PAD_ONE(x) (1ULL << 63) >> ((7 - (x % 8)) * 8)
#define U64_BE_PAD_ONE(x) (1ULL << 63) >> ((x % 8) * 8)

uint32_t	md_pad_u8_to_u64(char *in, uint64_t *out, uint8_t type)
{
	uint64_t	len;
	uint64_t	out_len;
	uint64_t	i;

	len = ft_strlen(in);
	i = (len * 8) + 129;
	out_len = (i + (1024 - (i % 1024))) / 64;
	if ((out = malloc(sizeof(*out) * out_len)))
	{
		if (type == LITTLE_ENDIAN)
			i = u8_to_u64_le(&out, in, len);
		else
			i = u8_to_u64_be(&out, in, len);
		out[i++] += (type == LE ? U64_LE_PAD_ONE(len) : U64_BE_PAD_ONE(len));
		while (i < out_len - 2)
			out[i++] = 0;
		out[i++] = (type == LE ? U64_LE_DIGIT1(len) : U64_BE_DIGIT1(len));
		out[i] = (type == LE ? U64_LE_DIGIT2(len) : U64_BE_DIGIT2(len));
	}
	return (chunk->len);
}
