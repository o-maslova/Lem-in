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
# define ROOMS graph->rooms
# define END graph->end_room

int					g_fd;
int					g_ants;
int					g_end;
int					g_amount;

typedef struct		s_link
{
	int				pos;
	struct s_link	*next;
}					t_link;

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


typedef struct		s_path
{
	int				*path;
	int				p_val;
	int				ant;
	int				i;
	int				j;
	int				k;
	struct s_path	*next;

}					t_path;

typedef struct		s_graph
{
	int				ant_amount;
	int				end_room;
	int				rooms;
	int				p_num;
	int				**links;
	char			**arr;
	t_vert			*graph;
	t_path			*pathes;
}					t_graph;

typedef struct		s_algo
{
	int				*distances;
	int				*prev;
	int				*visited;
	int				*queue;
	int				index;
}					t_algo;

t_vert				*vertex_create(t_graph *graph, char **arr, int pos);
void				add_vertex(t_vert **graph, t_vert *nw);
int					add_path(t_path **variants, t_path *path);
void				add_node(t_graph **graph, char **arr, int pos);
void				sort_path(t_path *list);
t_path				*create_path(t_graph *graph, t_algo *algo_stuff, int *used);
t_path				*deeper(t_algo *algo, t_graph *graph, int *used);
void				initial(t_algo **algo, int num);

void				make_name_arr(t_graph *graph);
void				make_path_arr(t_graph *graph);
void				clear_graph(t_vert **graph);
void				clear_vertex(t_vert *vrt);
void				clear_path(t_path **path);
void				clear_matrix(int **links, int amount);
void				clear_arr(char **arr);
void				error_handling(int num, char **arr, t_graph **graph);
void				check_s_e(t_graph **graph, int n);
int					check_err(char *line, t_graph **graph, int n, int pos);
int					check_link(char *line);
// int					list_fulling(int fd, t_vert **graph, char **line, int pos);
// int					making_links(char *line, t_vert **graph, int **links);
void				memory_allocate(t_graph **graph, int *check);
void				parsing(int fd, t_graph **graph);
// void				match(int *arr, int *path, int amount);
// void				match_column(int **links, int k, int amount);
// void				unmatch(t_graph *graph, int limit);
void				algorithm(t_graph *graph);
void				ant_output(t_graph *graph);

void				print_graph(t_graph *graph);
void				print_matrix(int fd, t_graph graph);
void				print_path(t_link *path);
void				print_variants(int fd, t_path *path);
void				printf_this(int *arr);

#endif
