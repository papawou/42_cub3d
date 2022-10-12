NAME := cub3D

CFLAGS := -Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -Wno-unused-variable -g -fdiagnostics-color=always
endif

LIBS := ./libs/mlx/libmlx.a
LIBS_BIN := -framework OpenGL -framework AppKit -lm
LIBSINC := -I./libs/mlx
INC := -I./inc

SRCS := main.c

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