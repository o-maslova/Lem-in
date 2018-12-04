#ifndef LEM_IN
# define LEM_IN
# include "./libft/ft_printf/ft_printf.h"

int					g_fd;
int					g_ants;
int					g_amount;

typedef struct		s_link
{
	char			*name;
	int				pos;
	struct s_link	*next;
}					t_link;

typedef struct		s_coords
{
	int				pos;
	int				is_start;
	int				is_end;
	int				if_visit;
	char			*name;
	int				x;
	int				y;
	t_link			*links;
	struct s_coords	*next;
}					t_coords;



t_coords			*vertex_create(char **arr, int pos);
t_link				*link_add(t_link *list, char *s, int pos);
void				add_vertex(t_coords **list, t_coords *vertex);
void				clear_list(t_coords **list);
void				clear_vertex(t_coords *vertex);
void				error_handling(int num, char **arr, t_coords **v);
void				check_s_e(int fd, char **line, t_coords **list, int n);
int					check_err(char *line, t_coords **list, int n, int pos);
int					check_link(char *line);

#endif