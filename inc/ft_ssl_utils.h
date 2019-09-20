/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ft_ssl_utils.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/09/17 12:26:09 by pheilbro          #+#    #+#             */
/*   Updated: 2019/09/18 08:59:07 by pheilbro         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FT_SSL_UTILS_H
# define FT_SSL_UTILS_H

# include <stdint.h>

# define U64_BE_DIGIT1 0xFF00000000000000
# define U64_BE_DIGIT2 0xFF000000000000
# define U64_BE_DIGIT3 0xFF0000000000
# define U64_BE_DIGIT4 0xFF00000000
# define U32_BE_DIGIT1 0xFF000000
# define U32_BE_DIGIT2 0xFF0000
# define U32_BE_DIGIT3 0xFF00
# define U32_BE_DIGIT4 0xFF

# define U64_BE_SHIFT1 56
# define U64_BE_SHIFT2 48
# define U64_BE_SHIFT3 40
# define U64_BE_SHIFT4 32
# define U32_BE_SHIFT1 24
# define U32_BE_SHIFT2 16
# define U32_BE_SHIFT3 8

# define U32_LE_DIGIT1 0xFF
# define U32_LE_DIGIT2 0xFF00
# define U32_LE_DIGIT3 0xFF0000
# define U32_LE_DIGIT4 0xFF000000
# define U64_LE_DIGIT1 0xFF00000000
# define U64_LE_DIGIT2 0xFF0000000000
# define U64_LE_DIGIT3 0xFF000000000000
# define U64_LE_DIGIT4 0xFF00000000000000

# define U32_LE_SHIFT2 8
# define U32_LE_SHIFT3 16
# define U32_LE_SHIFT4 24
# define U64_LE_SHIFT1 32
# define U64_LE_SHIFT2 40
# define U64_LE_SHIFT3 48
# define U64_LE_SHIFT4 56

int			u32_be_to_u8(uint32_t *in, uint8_t **out, uint8_t len);
int			u32_le_to_u8(uint32_t *in, uint8_t **out, uint8_t len);
int			u64_be_to_u8(uint64_t *in, uint8_t **out, uint8_t len);
int			u64_le_to_u8(uint64_t *in, uint8_t **out, uint8_t len);
int			u8_to_u32_be(uint8_t *in, uint32_t **out, int len);
int			u8_to_u32_le(uint8_t *in, uint32_t **out, int len);
int			u8_to_u64_be(uint8_t *in, uint64_t **out, int len);
int			u8_to_u64_le(uint8_t *in, uint64_t **out, int len);
uint32_t	md_pad_u8_to_u32(char *in, uint32_t *out, uint8_t type);
uint64_t	md_pad_u8_to_u64(char *in, uint64_t *out, uint8_t type);
uint64_t	rot_l(uint64_t x, uint8_t shift, uint8_t data_size);
uint64_t	rot_r(uint64_t x, uint8_t shift, uint8_t data_size);

#endif
