NAME			:=	cub3D

HEADERS_DIR		:=	includes
HEADERS_FILES	:=	cub3d.h

HEADERS			:= $(addprefix $(HEADERS_DIR)/, $(HEADERS_FILES))

SRC_DIR			:=	sources
SRC_FILES		:=	map_parsing.c \
					utils/window_utils.c

SRCS			:= $(addprefix $(SRC_DIR)/, $(SRC_FILES))

LIB_NAMES		:=	lib/libft
LIBS			=	$(subst lib,-l,$(notdir $(LIB_NAMES)))
LIB_LD			=	$(foreach lib,$(LIB_NAMES),-L$(lib))
LIB_PATHS		=	$(foreach lib,$(LIB_NAMES),$(lib)/$(notdir $(lib)).a)
LIB_HEADERS		=	$(foreach lib,$(LIB_NAMES),-I$(lib)/inc/)

LIB_PATHS		+=	lib/minilibx_opengl_20191021/libmlx_Linux.a
LIB_HEADERS		+= -Ilib/minilibx_opengl_20191021
LIBS			+= -framework OpenGL -framework AppKit -g -lmlx -Llib/minilibx_opengl_20191021
LIB_LD			+= -Llib/minilibx_opengl_20191021

BUILD_DIR		:=	.build
OBJS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.o)
DEPS			:=	$(SRC_FILES:%.c=$(BUILD_DIR)/%.d)
CCDEPS			:=	NAME=\"$(NAME)\"

# Compiler options
CC				:=	cc
DEBUG_FLAG		:=	#-fsanitize=address
CC_FLAGS		:=	-Wextra -Werror -Wall -O3 $(DEBUG_FLAG)
CC_DEPS_FLAGS	:=	-MP -MMD
CC_DEFS_FLAGS	:=	$(foreach def,$(CCDEPS),-D $(def))

MAKE			:=	make -C

#########################
# 		RULES			#
#########################

all: $(NAME)

$(LIB_PATHS): force
	$(MAKE) lib/libft
	$(MAKE) lib/minilibx_opengl_20191021

$(NAME): $(OBJS)
	$(CC) -g3 $(CC_FLAGS) $(OBJS) $(LIB_LD) $(LIBS) -o $@

-include $(DEPS)

$(BUILD_DIR)/%.o: $(SRC_DIR)/%.c $(LIB_PATHS) Makefile
	@mkdir -p $(@D)
	$(CC) $(CC_FLAGS)  -g3 $(CC_DEPS_FLAGS) $(CC_DEFS_FLAGS) -I$(HEADERS_DIR) $(LIB_HEADERS) -c $< -o $@

clean:
	$(MAKE) lib/libft clean
	$(MAKE) lib/minilibx_opengl_20191021 clean
	@rm -rf $(BUILD_DIR)
	@rm -rf $(BUILD_DIR_B)

fclean: clean
	$(MAKE) lib/libft fclean
	@rm -rf $(NAME)

re: fclean all

.PHONY: all clean fclean re force
