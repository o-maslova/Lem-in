NAME = lem-in
LIB = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror -g
SRCDIR = ./src/
HDIR = ./include/
SRC = main.c \
		vertex_staff.c \
		clear_staff.c \
		errors.c \
		check.c \
		algorithm.c \
		path_staff.c \
		parsing.c \
		find_pathes.c \
		ant_output.c \

HEADER = ./lem_in.h
DSRC = $(addprefix $(SRCDIR), $(SRC))
DINC = $(addprefix $(HDIR), $(HEADER))
BINS = $(DSRC:.c=.o)

all: lib $(NAME)

lib:
	make -C libft

$(NAME): $(BINS) $(LIB)
	gcc -o $(NAME) $(BINS) $(LIB)

%.o: %.c $(DINC)
	gcc $(FLAGS) -o $@ -c $< -I libft -I $(HDIR)

clean:
	make clean -C libft
	/bin/rm -f $(BINS)
	/bin/rm -f *~

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME)

re: fclean all