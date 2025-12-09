# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: rkowalsk <rkowalsk@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2020/02/17 15:52:56 by rkowalsk          #+#    #+#              #
#    Updated: 2021/06/14 17:24:34 by rkowalsk         ###   ########lyon.fr    #
#                                                                              #
# **************************************************************************** #

NAME = libft.a
SRCS =	ft_isalnum.c \
		ft_bzero.c \
		ft_isalpha.c \
		ft_isascii.c \
		ft_isdigit.c \
		ft_isprint.c \
		ft_memccpy.c \
		ft_memchr.c \
		ft_memcmp.c \
		ft_memcpy.c \
		ft_strlen.c \
		ft_memmove.c \
		ft_memset.c \
		ft_strchr.c \
		ft_strnchr.c \
		ft_strncmp.c \
		ft_strcmp.c \
		ft_strrchr.c \
		ft_tolower.c \
		ft_toupper.c \
		ft_strlcpy.c \
		ft_strnstr.c \
		ft_strlcat.c \
		ft_itoa.c \
		ft_uitoa.c \
		ft_atoi.c
FLAGS = -Wall -Wextra -Werror -m32 -O2 -ffreestanding -fno-builtin -fno-exceptions -fno-stack-protector -nostdlib -nodefaultlibs
HEADER = libft.h
OBJS = ${SRCS:.c=.o}

.PHONY: all
.PHONY: clean
.PHONY: fclean
.PHONY: re 

$(NAME): $(OBJS)
	ar rc $(NAME) $(OBJS)

$(OBJS): %.o: %.c $(HEADER)
	gcc $(FLAGS) -c $< -o $@
	
all: $(NAME)

clean:
	rm -f $(OBJS)

fclean: clean
	rm -f $(NAME)

re: fclean all
