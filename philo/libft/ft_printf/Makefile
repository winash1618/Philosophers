# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/02/27 04:47:02 by mkaruvan          #+#    #+#              #
#    Updated: 2022/04/30 07:20:34 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME =	libftprintf.a

SRCS = ft_putchar.c	ft_putint.c	ft_putunint.c ft_printf.c	ft_putaddr.c \
   	   ft_puthex.c	ft_putstr.c ft_puthexcap.c

LIBFT_DIR	=	../

LIBFT		=	libft.a

INC_DIR		=	includes

SRC_DIR		=	srcs

OBJ_DIR		=	objs

OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%c=%o))

LIB_AR		=	ar rcs

CC			=	gcc

CFLAGS		=	-Wall -Wextra -Werror

RM			=	rm -rf

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
				@mkdir -p $(OBJ_DIR)
				@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -c $< -o $@

$(NAME):		$(LIBFT) $(OBJS)
				@$(LIB_AR) $(NAME) $(OBJS)

$(LIBFT):	
				@make -C $(LIBFT_DIR)
				@cp $(LIBFT_DIR)/$(LIBFT) $(NAME)
				
all:			$(NAME)

clean:
				@make -C $(LIBFT_DIR) fclean
				@$(RM) $(OBJ_DIR)

fclean:			clean
				@$(RM) $(NAME)

re:				fclean all

norm:
			@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			@norminette -R CheckDefine $(INC_DIR)/*.h
			@make -C $(LIBFT_DIR) norm

.PHONY:			all clean fclean norm re