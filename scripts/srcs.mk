SRC_PATH=src/

SRC_NAME=	free.c\
			malloc.c\
			realloc.c\
			zones_init.c\
			zones_split.c\
			singletons.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))
