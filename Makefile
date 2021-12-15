ifeq ($(HOSTTYPE),)
HOSTTYPE := $(shell uname -m)_$(shell uname -s)
endif

NAME_PREFIX = libft_malloc
NAME = $(NAME_PREFIX)$(HOSTTYPE).so

CC=gcc
FLAGS=-Wall -Werror -Wextra

ifeq ($(shell uname -s), "Darwin")
	FLAGS += -Weverything
endif

SCRIPT_PATH=scripts/
include $(SCRIPT_PATH)/srcs.mk
include $(SCRIPT_PATH)/includes.mk

OBJ=$(SRC:.c=.o)

LIB_PATH=libft/
LIB=$(LIB_PATH)libft.a

all: $(LIB) $(NAME) $(LINK)

$(LIB): $(LIB_PATH)
	make -C $(LIB_PATH)

$(NAME): $(OBJ)
	$(CC) -shared $(OBJ) -o $(NAME) $(LIB)
	ln -s $(NAME) libft_malloc.so

$(SRC_PATH)%.o: $(SRC_PATH)%.c $(INC)
	$(CC) $(FLAGS) -I$(INC_PATH) -I$(LIB_PATH) -fPIC -o $@ -c $<

clean:
	rm -rf $(OBJ)
	make -C $(LIB_PATH) clean

fclean: clean
	rm -rf $(NAME)
	rm -rf libft_malloc.so
	make -C $(LIB_PATH) fclean

re: fclean all
