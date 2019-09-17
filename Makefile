# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: pheilbro <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2019/08/29 17:20:30 by pheilbro          #+#    #+#              #
#    Updated: 2019/09/17 14:04:42 by pheilbro         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		= ft_ssl

CC			= gcc
LIB			= -L../libft -lft
INC_FLAGS	= -I inc -I ../libft/inc
CFLAGS		= -Wall -Werror -Wextra
DEBUG_FLAGS	= -g -fsanitize=address

SRC_DIR		= src
OBJ_DIR		= obj

SRC			= main get_info parse_input parse_options error usage clean \
			  read_data
UTILS		= rotate md_pad_u8_to_u32 md_pad_u8_to_u64 \
			  u32_be_to_u8 u32_le_to_u8 u64_be_to_u8 u64_le_to_u8 \
			  u8_to_u32_be u8_to_u32_le u8_to_u64_be u8_to_u64_le
MD			= parse_message_digest process_message_digest print_message_digest \
			  u32_md_block_utils u64_md_block_utils \
			  algorithms/ft_ssl_md5 \
			  algorithms/ft_ssl_sha1 \
			  algorithms/ft_ssl_sha224 \
			  algorithms/ft_ssl_sha256 algorithms/ft_ssl_sha256_aux \
			  algorithms/ft_ssl_sha384 \
			  algorithms/ft_ssl_sha512 algorithms/ft_ssl_sha512_aux \
			  algorithms/ft_ssl_sha512_224 algorithms/ft_ssl_sha512_256 \
			  #algorithms/ft_ssl_whirlpool \#
			  algorithms/ft_ssl_sha_utils
CIPHER		= parse_cipher \
			  algorithms/ft_ssl_base64 \
			  algorithms/ft_ssl_des \
			  algorithms/ft_ssl_pbkdf
STANDARD	= parse_standard

OBJ			= $(patsubst %, $(OBJ_DIR)/%.o, \
		$(patsubst %, utils/%, $(UTILS)) \
		$(patsubst %, message_digest/%, $(MD)) \
		$(patsubst %, cipher/%, $(CIPHER)) \
		$(patsubst %, standard/%, $(STANDARD)))

all: $(NAME)

$(NAME): $(OBJ) ../libft/libft.a
	@$(CC) $(CFLAGS) $(LIB) -o $@ $^

../libft/libft.a:
	@make -sC libft

$(OBJ_DIR)/%.o: $(SRC_DIR)/%.c 
	@echo Compiling $<.
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) $(INC_FLAGS) -c $< -o $@

debug: 
	$(CC) $(FLAGS) $(DEBUG_FLAGS) $(INC_FLAGS) src/*.c \
		src/*/*.c src/*/*/*.c \
		../libft/src/*/*.c ../libft/src/stdio/ft_printf/*.c \
		../libft/src/stdio/ft_printf/*/*.c

clean: clean_debug
	#make clean -C lib/
	rm -rf $(OBJ_DIR)

clean_debug:
	rm -f debug 
	rm -rf debug.dSYM 

fclean: clean clean_debug
	#make fclean -C lib/
	rm -f $(NAME)

re: fclean all
