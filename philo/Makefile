# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: mkaruvan <mkaruvan@student.42.fr>          +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2022/04/28 14:26:37 by mkaruvan          #+#    #+#              #
#    Updated: 2022/04/30 10:52:08 by mkaruvan         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

NAME		=	philo

LIBFT		=	libftprintf.a

LIBFT_DIR	=	libft/ft_printf

INC_DIR		=	includes

SRC_DIR		=	srcs

OBJ_DIR		=	objs

SRCS		=	utils.c events.c philo.c main.c

OBJS		=	$(addprefix $(OBJ_DIR)/, $(SRCS:%c=%o))

CC			=	gcc

CFLAGS		=	-pthread -g -Wall -Wextra -Werror

LIB_AR		=	ar rcs

RM			=	rm -rf

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
			@mkdir -p $(OBJ_DIR)
			@$(CC) $(CFLAGS) -I $(INC_DIR) -I $(LIBFT_DIR)/$(INC_DIR) -c $< -o $@

all:		$(LIBFT) $(NAME)
		
$(NAME):	$(OBJS)
			@$(CC) $(CFLAGS) $(LIBFT_DIR)/$(LIBFT) $(OBJS) -o $@

$(LIBFT):
			@make -C $(LIBFT_DIR)

clean:
			@$(RM) $(OBJ_DIR)
			@make -C $(LIBFT_DIR) clean

fclean:		clean
			@$(RM) $(NAME)
			@make -C $(LIBFT_DIR) fclean

norm:
			make -C $(LIBFT_DIR) norm
			norminette -R CheckForbiddenSourceHeader $(SRC_DIR)/*.c
			norminette -R CheckDefine $(INC_DIR)/*.h

re:			fclean all

.PHONY:		all clean fclean re bonus
