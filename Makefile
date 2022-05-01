# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 14:26:37 by mkaruvan          #+#    #+#              #
#    Updated: 2022/04/30 18:11:08 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

INC_DIR		=	includes

SRC_DIR		=	srcs

OBJ_DIR		=	objs

SRCS		=	utils.c events.c philo.c main.c ft_putchar.c \
				ft_putint.c ft_printf.c ft_putstr.c

OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%c=%o))

CC			=	gcc

CFLAGS		=	-pthread -g3 -Wall -Wextra -Werror

LIB_AR		=	ar rcs

RM			=	rm -rf

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) -I $(INC_DIR)  -c $< -o $@

all:		$(NAME)
		
$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(OBJS) -o $@


clean:
			@$(RM) $(OBJ_DIR)

fclean:		clean
			@$(RM) $(NAME)

norm:
			@norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			@norminette -R CheckDefine $(INC_DIR)/*.h

re:			fclean all

.PHONY:		all clean fclean re bonus
