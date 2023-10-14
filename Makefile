# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: marobert <marobert@student.42lyon.fr>      +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2023/06/01 14:31:07 by marobert          #+#    #+#              #
#    Updated: 2023/06/05 13:14:22 by marobert         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

#	Colors from https://misc.flogisoft.com/bash/tip_colors_and_formatting#colors1
RED			=	\033[31m
GREEN		=	\033[32m
CYAN		=	\033[34m
IGREY		=	\033[0;48m
END			=	\033[0m
ERASE		=	\033[2K\r

NAME			:=	cub3D

SRC_DIR			:=	sources
SRC_FILES		:=	main.c \
					parsing/map_parsing.c parsing/map_check.c parsing/map_borders_check.c \
					parsing/map_fillers.c parsing/colors_parsing.c parsing/parsing.c \
					parsing/parsing_utils.c \
					graphics/graphics.c graphics/player.c \
					graphics/drawing/raycasting.c graphics/drawing/drawing.c graphics/drawing/mini_map.c \
					graphics/textures/textures.c graphics/textures/get_texture_pixel.c \
					events.c

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

OS			=	$(shell uname)

ifeq ($(OS), Darwin) # MACOS

DIR_INCS	=	lib/minilibx-opengl
MLX_DIR		=	lib/minilibx-opengl
MLX			=	lib/minilibx-opengl/libmlx.a
MLX_FLAGS	=	-framework OpenGL -framework AppKit
CFLAGS		=	-D DARWIN=1

endif

ifeq ($(OS), Linux) #LINUX

DIR_INCS	=	lib/minilibx-linux
MLX_DIR		=	lib/minilibx-linux
MLX			=	lib/minilibx-linux/libmlx.a
MLX_FLAGS	=	-Llib/minilibx-linux -lX11 -lXext -lz -lmlx -lm
CFLAGS		=	-D LINUX=1

endif

MY_INCS		=	lib/libft/inc includes
DIR_INCS	+=	$(MY_INCS)
DIR_BUILD	=	.build/
OBJS		=	$(patsubst %.c, $(DIR_BUILD)%.o, $(SRCS))
DEPS		=	$(patsubst %.c, $(DIR_BUILD)%.d, $(SRCS))
LIBFT		=	lib/libft/libft.a
LIBFT_DIR	=	lib/libft
DEPS_FLAGS	=	-MMD -MP
CC			=	cc
RM			=	rm -rf
CFLAGS		+=	-Wall -Wextra -Werror -g3 -O3 #-fsanitize=address
CFLAGS		+=	#-I/usr/local/opt/readline/include -L/usr/local/opt/readline/lib -g3
NAME		=	cub3D

all:		libft mlx $(NAME)

$(NAME):	$(LIBFT) $(MLX) $(OBJS)
			@printf "[$(CYAN)Compiling$(END)] % 25s" $(NAME)
			@$(CC) $(CFLAGS) $(DIR_INCS:%=-I %) -o $(NAME) $(OBJS) $(LIBFT) $(MLX) $(MLX_FLAGS)
			@printf "$(ERASE)[$(GREEN)Done$(END)] % 30s\n" $(NAME)

.PHONY:		norme
norme:
			@norminette $(SRCS) $(MY_INCS) | grep -v 'OK!'

.PHONY:		libft
libft:
			@make -C $(LIBFT_DIR)

.PHONY:		mlx
mlx:
			@make -C $(MLX_DIR)

-include $(DEPS)

$(DIR_BUILD)%.o : %.c
			@printf "[$(CYAN)Compiling$(END)] % 25s" $(patsubst $(shell dirname $<)/%, %, $<)
			@mkdir -p $(shell dirname $@)
			@$(CC) $(CFLAGS) $(DEPS_FLAGS) $(DIR_INCS:%=-I %) -c $< -o $@
			@printf "$(ERASE)[$(GREEN)Done$(END)] % 30s\n" $(patsubst $(shell dirname $<)/%, %, $<)

clean:
			@$(RM) $(DIR_BUILD)
			@printf "[$(RED)Deleted$(END)] % 27s\n" "$(NAME) objects"

fclean:		clean
			@$(RM) $(NAME)
			@printf "[$(RED)Deleted$(END)] % 27s\n" $(NAME)

re:			fclean
			@make all

.PHONY: all clean fclean re force
