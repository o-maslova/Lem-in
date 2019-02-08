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
# include "./ft_printf/ft_printf.h"
# include <stdio.h>
# define ROOMS graph->rooms
# define END graph->end_room
# define RED "\033[0;31m"
# define YELLOW "\033[0;33m"
# define WHITE "\033[0;37m"
# define NC "\033[0m"

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
	char			*path_color;
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
	int				c_flag;
	int				str;
	int				ant_amount;
	int				ant_in_string;
	int				is_neg;
	int				end_room;
	int				rooms;
	int				p_num;
	int				**links;
	char			**arr;
	char			**colors;
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
void				add_vertex(t_graph **graph, t_vert **rooms, t_vert *nw);
int					add_path(t_graph *graph, t_path **variants, t_path *path);
void				add_node(t_graph **graph, char **arr, int pos);
void				sort_path(t_path *list);
t_path				*create_path(t_graph *graph, t_algo *algo_stuff, int *used);
t_path				*deeper(t_algo *algo, t_graph *graph, int *used);
void				initial(t_algo **algo, int num);
void				make_name_arr(t_graph *graph);
int					search_by_name(t_vert *graph, char *name, int i);
void				clear_graph(t_vert **graph);
void				clear_vertex(t_vert *vrt);
void				clear_path(t_path **path);
void				clear_matrix(int **links, int amount);
void				clear_arr(char **arr);
void				error_handling(int num, char **arr, t_graph **graph);
void				check_start_end(t_graph **gr, int n, char **line);
int					check_err(char *line, t_graph **graph, int n, int pos);
int					check_link(char *line);
void				check_graph(t_graph *graph);
void				memory_allocate(t_graph **graph, int *check);
void				pars_data(t_graph **graph);
void				algorithm(t_graph *graph, t_algo **algo);
void				ant_output(t_graph *graph);

#endif
