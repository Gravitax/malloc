SRC_PATH=src/

SRC_NAME=	free.c\
			malloc.c\
			realloc.c\
			chunks.c\
			zones.c\
			singletons.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))
