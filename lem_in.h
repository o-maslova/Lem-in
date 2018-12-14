#ifndef LEM_IN
# define LEM_IN
# define START (*graph)->pos
# define END (*graph)
# define VRTX_NUM vrt->pos
# include "./libft/ft_printf/ft_printf.h"

int					g_fd;
int					g_ants;
int					g_start;
int					g_end;
int					g_amount;

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
	struct s_vert	*next;
}					t_vert;

typedef struct		s_link
{
	int				pos;
	struct s_link	*next;
}					t_link;

typedef struct		s_path
{
	int				*path;
	int				path_val;
	struct s_path	*next;
}					t_path;

t_vert				*vertex_create(char **arr, int pos);
// t_link				*create_link(int pos);
void				add_link(t_link **path, int pos);
void				add_vertex(t_vert **graph, t_vert *nw);
void				add_path(t_path **variants, t_path *path);
t_path				*create_path(t_link *link);
void				clear_graph(t_vert **graph);
void				clear_vertex(t_vert *vrt);
void				clear_link(t_link **link);
void				clear_path(t_path **path);
void				clear_matrix(int **links);
void				error_handling(int num, char **arr, t_vert **graph);
void				check_s_e(int fd, char **line, t_vert **graph, int n);
int					check_err(char *line, t_vert **graph, int n, int pos);
int					check_link(char *line);
int					search_by_name(t_vert *graph, char *name);
t_vert				*search_by_pos(t_vert *graph, int pos);
void				new_algo(int **links);
void				print_graph(t_vert *graph);

void		print_matrix(int **links);

#endif