#ifndef LEM_IN
# define LEM_IN
# include "./libft/ft_printf/ft_printf.h"

int					g_fd;
int					g_ants;

typedef struct		s_link
{
	char			*name;
	struct s_link	*next;
}					t_link;

typedef struct		s_coords
{
	int				is_start;
	int				is_end;
	char			*name;
	int				x;
	int				y;
	t_link			*links;
	struct s_coords	*next;
}					t_coords;

t_coords			*vertex_create(char **arr, int pos);
t_link				*link_add(t_link *list, char *s);
void				add_vertex(t_coords **list, t_coords *vertex);
void				clear_vertex(t_coords **vertex);
void				error_handling(int num, char **arr, t_coords **v);

#endif