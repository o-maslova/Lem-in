NAME = lem-in
LIB = ./libft/libft.a
FLAGS = -Wall -Wextra -Werror -g
SRC = ./main.c \
		./vertex_staff.c \
		./clear_staff.c \
		./errors.c \
		./check.c \
		./algorithm.c \
		./search.c \
		./link_staff.c \
		./path_staff.c \
		./print_staff.c

BINS = $(SRC:.c=.o)
HEADER = ./lem_in.h

all: lib $(NAME)

lib:
	make -C libft

$(NAME): $(BINS) $(LIB)
	gcc -o $(NAME) $(BINS) $(LIB)

%.o: %.c $(HEADER)
	gcc $(FLAGS) -o $@ -c $< -I libft

clean:
	make clean -C libft
	/bin/rm -f $(BINS)
	/bin/rm -f *~

fclean: clean
	make fclean -C libft
	/bin/rm -f $(NAME)

re: fclean all