/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   lem_in.h                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:08:38 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:08:39 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef LEM_IN_H
# define LEM_IN_H
# include "./libft/ft_printf/ft_printf.h"

int					g_fd;
int					g_ants;
int					g_end;
int					g_amount;

typedef struct		s_vert
{
	int				pos;
	int				is_start;
	int				is_end;
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
void				add_link(t_link **path, int pos);
void				add_vertex(t_vert **graph, t_vert *nw);
void				add_path(t_path **variants, t_path *path);
void				add_node(t_vert **graph, char **arr, int pos);
t_path				*create_path(t_link *link);
void				clear_graph(t_vert **graph);
void				clear_vertex(t_vert *vrt);
void				clear_link(t_link **link);
void				clear_path(t_path **path);
void				clear_matrix(int **links);
void				error_handling(int num, char **arr, t_vert **graph);
void				check_s_e(t_vert **graph, int n);
int					check_err(char *line, t_vert **graph, int n, int pos);
int					check_link(char *line);
int					search_by_name(t_vert *graph, char *name);
// int					list_fulling(int fd, t_vert **graph, char **line, int pos);
// int					making_links(char *line, t_vert **graph, int **links);
int					count_link_elem(t_link *list);
int					**memory_allocate(int *check);
t_vert				search_by_pos(t_vert *graph, int pos);
int					**parsing(int fd, t_vert **graph, int **links);
void				algorithm(int **links);

void				print_graph(t_vert *graph);
void				print_matrix(int fd, int **links);
void				print_path(t_link *path);
void				print_variants(int fd, t_path *path);

#endif
