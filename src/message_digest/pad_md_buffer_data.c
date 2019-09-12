/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   pad_buffer_data.c                                  :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/11 16:10:27 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/11 16:49:44 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#define U32_LE_DIGIT1(x) (uint32_t)(x * 8) / (1ULL << 32)
#define U32_LE_DIGIT2(x) (uint32_t)(x * 8) % (1ULL << 32)
#define U32_BE_DIGIT1(x) (uint32_t)(x * 8) % (1ULL << 32)
#define U32_BE_DIGIT2(x) (uint32_t)(x * 8) / (1ULL << 32)

#define U32_LE_PAD_ONE(x) (1UL << 31) >> ((3 - (x % 4)) * 8)
#define U32_BE_PAD_ONE(x) (1UL << 31) >> ((x % 4) * 8)

#define U64_LE_DIGIT1(x) (x * 8)
#define U64_LE_DIGIT2(x) (x / (1ULL / 8) * 8)
#define U64_BE_DIGIT1(x) (x / (1ULL / 8) * 8)
#define U64_BE_DIGIT2(x) (x * 8)

#define U64_LE_PAD_ONE(x) (1ULL << 63) >> ((7 - (x % 8)) * 8)
#define U64_BE_PAD_ONE(x) (1ULL << 63) >> ((x % 8) * 8)

uint32_t	pad_u32_buffer_data(char *in, uint32_t *out, uint8_t type)
{
	uint64_t	len;
	uint64_t	out_len;
	uint64_t	i;

	len = ft_strlen(in);
	i = (len * 8) + 65;
	out_len = (i + (512 - (i % 512))) / 32;
	if ((out = malloc(sizeof(*out) * out_len)))
	{
		if (type == LITTLE_ENDIAN)
			i = prep_u32_little_end(&out, in, len);
		else
			i = prep_u32_big_end(&out, in, len);
		out[i++] += (type == LE ? U32_LE_PAD_ONE(len) : U32_BE_PAD_ONE(len));
		while (i < out_len - 2)
			out[i++] = 0;
		out[i++] = (type == LE ? U32_LE_DIGIT1(len) : U32_BE_DIGIT1(len));
		out[i] = (type == LE ? U32_LE_DIGIT2(len) : U32_BE_DIGIT2(len));
	}
	return (chunk->len);
}

uint32_t	pad_u64_buffer_data(char *in, uint64_t *out, uint8_t type)
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
			i = prep_u64_little_end(&out, in, len);
		else
			i = prep_u64_big_end(&out, in, len);
		out[i++] += (type == LE ? U64_LE_PAD_ONE(len) : U64_BE_PAD_ONE(len));
		while (i < out_len - 2)
			out[i++] = 0;
		out[i++] = (type == LE ? U64_LE_DIGIT1(len) : U64_BE_DIGIT1(len));
		out[i] = (type == LE ? U64_LE_DIGIT2(len) : U64_BE_DIGIT2(len));
	}
	return (chunk->len);
}
