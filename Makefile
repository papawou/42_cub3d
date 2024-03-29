NAME := cub3D

CFLAGS := -Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -Wno-unused-variable -g -fdiagnostics-color=always
endif

LIBS := ./libs/mlx/libmlx.a ./libs/libft/libft.a
LIBS_BIN := -framework OpenGL -framework AppKit -lm
LIBSINC := -I./libs/mlx -I./libs/libft/inc
INC := -I./inc

SRCS := main.c\
		parser/parser.c	parser/parser_clean.c	parser/parser_map.c parser/check_map.c\
		gnl/get_next_line.c	gnl/get_next_line_utils.c\
		scene.c\
		map.c

SRCS += ftmlx/color/color.c ftmlx/ftmlx.c\
ftmlx/graphics/cam.c ftmlx/graphics/print/put_line.c\
ftmlx/img.c ftmlx/img_2.c\
ftmlx/math/mat.c ftmlx/math/quat.c ftmlx/math/quat_2.c ftmlx/math/rot.c ftmlx/math/trans.c ftmlx/math/trans_2.c\
ftmlx/math/utils.c ftmlx/math/utils_2.c\
ftmlx/math/vec.c ftmlx/math/vec_2.c

SRC_DIR := ./src
SRC := ${addprefix $(SRC_DIR)/, $(SRCS)}
OBJ_DIR := ./obj
OBJ := ${addprefix $(OBJ_DIR)/, ${SRCS:.c=.o}}

all : $(NAME)

$(NAME) : $(OBJ) $(LIBS)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBSINC) $(LIBS) $(LIBS_BIN)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC) $(LIBSINC)

%.a :
	cd $(@D) && $(MAKE)

clean:
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re