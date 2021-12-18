SRC_PATH=src/

SRC_NAME=	free.c\
			malloc.c\
			realloc.c\
			show_alloc_mem.c\
			chunks.c\
			zones.c\
			singletons.c

SRC=$(addprefix $(SRC_PATH), $(SRC_NAME))
