# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2021/12/22 14:38:28 by mkaruvan          #+#    #+#              #
#    Updated: 2022/04/29 16:43:45 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

SRCS			=	ft_isalpha.c ft_isdigit.c ft_isalnum.c ft_isascii.c \
					ft_isprint.c ft_strlen.c ft_memset.c ft_bzero.c \
					ft_memcpy.c ft_memmove.c ft_strlcpy.c ft_strlcat.c \
					ft_toupper.c ft_tolower.c ft_strchr.c ft_strrchr.c \
					ft_strncmp.c ft_memchr.c ft_memcmp.c ft_strnstr.c \
					ft_atoi.c ft_calloc.c ft_strdup.c ft_split.c ft_strtrim.c \
					ft_putchar_fd.c ft_putendl_fd.c ft_putstr_fd.c \
					ft_putnbr_fd.c ft_substr.c ft_strmapi.c ft_striteri.c \
					ft_strjoin.c ft_itoa.c

INC_DIR		=	includes

SRC_DIR		=	srcs

OBJ_DIR		=	objs

OBJ_SRC			= $(addprefix $(OBJ_DIR)/, $(SRCS:%c=%o))

CC				= gcc

RM				= rm -rf

CFLAGS			= -Wall -Wextra -Werror -I.

NAME			= libft.a

LIB_AR	= ar rcs

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -I $(INC_DIR) -c $< -o $@

all:			$(NAME)

$(NAME):		$(OBJ_SRC)
				@$(LIB_AR) $(NAME) $(OBJ_SRC)

clean:
				@$(RM) $(OBJ_DIR)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

norm:
			@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			@norminette -R CheckDefine $(INC_DIR)/*.h

.PHONY:			all clean fclean re norm
