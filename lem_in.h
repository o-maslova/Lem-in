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

typedef struct		s_graph
{
	int				ant_amount;
	int				end_room;
	int				rooms;
	int				pathes_num;
	int				**links;
	int				*starts;
	t_vert			*graph;
	t_path			*pathes;
}					t_graph;


t_vert				*vertex_create(t_graph *graph, char **arr, int pos);
void				add_link(t_link **path, int pos);
void				add_vertex(t_vert **graph, t_vert *nw);
void				add_path(t_path **variants, t_path *path);
void				add_node(t_graph **graph, char **arr, int pos);
void				sort_path(t_path *list);
t_path				*create_path(t_link *link);
void				clear_graph(t_vert **graph);
void				clear_vertex(t_vert *vrt);
void				clear_link(t_link **link);
void				clear_path(t_path **path);
void				clear_matrix(int **links, int amount);
void				error_handling(int num, char **arr, t_graph **graph);
void				check_s_e(t_graph **graph, int n);
int					check_err(char *line, t_graph **graph, int n, int pos);
int					check_link(char *line);
int					check_path(t_link *path, int amount);
int					search_by_name(t_vert *graph, char *name);
// int					list_fulling(int fd, t_vert **graph, char **line, int pos);
// int					making_links(char *line, t_vert **graph, int **links);
int					count_link_elem(t_link *list);
void				memory_allocate(t_graph **graph, int *check);
void				parsing(int fd, t_graph **graph);
void				match(int *arr, int *path, int amount);
void				match_column(int **links, int k, int amount);
void				unmatch(t_graph *graph, int limit);
void				remove_part(t_link **path, int pos);
void				remove_last(t_link **path);
void				algorithm(t_graph *graph);

void				print_graph(t_graph *graph);
void				print_matrix(int fd, t_graph graph);
void				print_path(t_link *path);
void				print_variants(int fd, t_path *path);
void				printf_this(int *arr);

#endif
