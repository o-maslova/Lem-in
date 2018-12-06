#ifndef LEM_IN
# define LEM_IN
# define START (*graph)->pos
# include "./libft/ft_printf/ft_printf.h"

int					g_fd;
int					g_ants;
int					g_start;


typedef struct		s_link
{
	char			*name;
	int				pos;
	struct s_link	*next;
}					t_link;

typedef struct		s_vert
{
	int				path_val;
	int				pos;
	int				is_start;
	int				is_end;
	int				if_visit;
	char			*name;
	int				x;
	int				y;
	t_link			*links;
	struct s_vert	*next;
}					t_vert;

typedef struct		s_path
{
	t_link			*path;
	int				path_val;
	struct s_path	*next;
}					t_path;

t_vert				*vertex_create(char **arr, int pos);
void				link_add(t_link **list, char *s, int pos);
void				add_vertex(t_vert **graph, t_vert *nw);
void				add_path(t_path **variants, t_link *path, int val);
void				clear_list(t_vert **graph);
void				clear_vertex(t_vert *vrt);
void				clear_visits(t_vert **graph);
void				error_handling(int num, char **arr, t_vert **graph);
void				check_s_e(int fd, char **line, t_vert **graph, int n);
int					check_err(char *line, t_vert **graph, int n, int pos);
int					check_link(char *line);
void				algorithm(t_vert **graph);
t_link				*dup_list(t_link *list);

void				print_graph(t_vert *graph);

#endif