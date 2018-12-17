NAME = lemin.visualisation
LIB = libft.a
GRAPHICS = -lmlx -framework OpenGL -framework AppKit
FLAGS = -Wall -Wextra -Werror
SRC = ./draw.c \
		./brezenhaim.c \
		../vertex_staff.c \
		../parsing.c \
		../check.c \
		../errors.c \
		../algorithm.c \
		../clear_staff.c \
		../path_staff.c \
		../link_staff.c \
		../print_staff.c \
		../search.c
BINS = $(SRC:.c=.o)
HEADER = ./view.h ../lem_in.h
LIB_DIR = ../libft/
EXE_DIR = ../
LIBFT = $(addprefix $(LIB_DIR), $(LIB))
EXE = $(addprefix $(EXE_DIR), $(NAME))

all: $(EXE)

$(EXE): $(BINS)
	gcc -o $(EXE) $(LIBFT) $(BINS) $(GRAPHICS)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -o $@ -c $< -I $(LIBFT)

clean:
	/bin/rm -f $(BINS)
	/bin/rm -f *~

fclean: clean
	/bin/rm -f $(EXE)

re: fclean all