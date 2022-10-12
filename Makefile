NAME := cub3D

CFLAGS := -Wall -Wextra -Werror
DEBUG ?= 0
ifeq ($(DEBUG), 1)
CFLAGS += -Wno-unused-variable -g -fdiagnostics-color=always
endif

LIBS := 
LIBSINC :=
INC := -I./inc

SRCS := main.c

SRC_DIR := ./src
SRC := ${addprefix $(SRC_DIR)/, $(SRCS)}
OBJ_DIR := ./obj
OBJ := ${addprefix $(OBJ_DIR)/, ${SRCS:.c=.o}}

all : $(NAME)

$(NAME) : $(OBJ)
	$(CC) $(CFLAGS) -o $@ $(OBJ) $(INC) $(LIBSINC) $(LIBS)

$(OBJ_DIR)/%.o : $(SRC_DIR)/%.c
	mkdir -p $(@D)
	$(CC) $(CFLAGS) -o $@ -c $< $(INC) $(LIBSINC)

clean:
	$(RM) $(OBJ)

fclean : clean
	$(RM) $(NAME)

re : fclean all

.PHONY : all clean fclean re