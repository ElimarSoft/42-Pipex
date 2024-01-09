# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: jsala-ba <jsala-ba@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/10/14 12:26:16 by jsala-ba          #+#    #+#              #
#    Updated: 2024/01/09 15:10:16 by jsala-ba         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME = pipex
NAME_BONUS = pipex_bonus
FSANITIZER_C = -fsanitize=address
FSANITIZER_L = -fsanitize=address

LIBFT1 = ft_strnstr.c ft_split.c ft_strlen.c ft_strjoin.c \
		ft_putchar_fd.c ft_putstr_fd.c ft_putendl_fd.c \
		ft_putnbr_fd.c ft_strdup.c ft_strncmp.c ft_calloc.c

LIBFT = $(addprefix libft/, $(LIBFT1))

SRCS = src/pipex.c src/pipex_aux.c src/get_env.c src/messages.c \
		src/pipex_is.c $(LIBFT)

SRCS_STD= $(SRCS) src/pipex_aux_std.c

SRCS_BONUS = $(SRCS) src/pipex_aux_bonus.c

CC = gcc
CFLAGS = -g3 -Wall -Wextra -I libft -I src #$(FSANITIZER_C)
LFLAGS = -L /usr/lib -lm #$(FSANITIZER_L)

RM = rm -f

OBJS_STD = $(SRCS_STD:.c=.o)
OBJS_BONUS = $(SRCS_BONUS:.c=.o)

all:	$(NAME)

bonus:	$(NAME_BONUS)

$(NAME): $(OBJS_STD)
	@$(CC) -o $(NAME) $(OBJS_STD) $(LFLAGS)

$(NAME_BONUS): $(OBJS_BONUS)
	@$(CC) -o $(NAME_BONUS) $(OBJS_BONUS) $(LFLAGS)

clean:
	$(RM) $(OBJS_STD) $(OBJS_BONUS)

fclean:	clean
	$(RM) $(NAME) $(NAME_BONUS)

re:	fclean all

re_bonus: fclean bonus

git:
	git add src/*.c
	git add src/*.h
	git add Makefile
	git add libft/*.c
	git add libft/*.h
