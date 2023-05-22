NAME			:=	cub3D

HEADERS_DIR		:=	includes
HEADERS_FILES	:=	cub3d.h

HEADERS			:= $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))

SRC_DIR			:=	sources
SRC_FILES		:=	main.c \
					parsing/map_parsing.c parsing/map_check.c parsing/map_borders_check.c \
					parsing/map_fillers.c parsing/colors_parsing.c parsing/parsing.c \
					graphics/graphics.c graphics/player.c \
					graphics/drawing/raycasting.c graphics/drawing/drawing.c graphics/drawing/mini_map.c \
					graphics/textures/textures.c graphics/textures/get_texture_pixel.c \

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIB_NAMES		:=	lib/libft
LIBS			=	$(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD			=	$(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS		=	$(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS		=	$(foreach lib,$(LIB_NAMES),-I$(lib)/inc/)

LIB_PATHS		+=	lib/minilibx-linux/libmlx_Linux.a
LIB_HEADERS		+= -Ilib/minilibx-linux
LIBS			+= -lmlx_Linux -lX11 -lXext -lz -lmlx -lm
LIB_LD			+= -Llib/minilibx-linux

BUILD_DIR		:=	build
OBJS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.d)
CCDEPS			:=	NAME=\"$(NAME)\"

# Compiler options
CC				:=	cc
DEBUG_FLAG		:=	-g3 -fsanitize=address
CC_FLAGS		:=	-Wextra -Werror -Wall -O3 #$(DEBUG_FLAG)
CC_DEPS_FLAGS	:=	-MP -MMD
CC_DEFS_FLAGS	:=	$(foreach def,$(CCDEPS),-D $(def))

MAKE			:=	make -C

#########################
# 		RULES			#
#########################

all: $(NAME)

$(LIB_PATHS): force
	$(MAKE) lib/libft
	$(MAKE) lib/minilibx-linux

$(NAME): $(OBJS)
	$(CC) -g3 $(CC_FLAGS) $(OBJS) $(LIB_LD) $(LIBS) -o $@

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_PATHS) Makefile
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS)  -g3 $(CC_DEPS_FLAGS) $(CC_DEFS_FLAGS) -I$(HEADERS_DIR) $(LIB_HEADERS) -c $< -o $@

clean:
	$(MAKE) lib/libft clean
	$(MAKE) lib/minilibx-linux clean
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_B)

fclean: clean
	$(MAKE) lib/libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re force
