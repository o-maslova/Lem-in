/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:04:49 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:05:48 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		deeper(t_path *variant, t_graph *graph, t_link **path, int i)
{
	int		k;

	k = 0;
	while (++k < graph->rooms)
	{
		if (graph->links[i][graph->end_room] == 1)
		{
			add_link(path, graph->end_room);
			variant = create_path(*path);
			add_path(&(graph->pathes), variant);
			return (1);
		}
		if (graph->links[i][k] == 1)
		{
			add_link(path, k);
			graph->links[i][k] = -1;
			graph->links[k][i] = -1;
			if ((deeper(variant, graph, path, k)) == 1)
				remove_part(path, k);
			else
				remove_last(path);
		}
	}
	free(variant);
	return (0);
}

void		output(t_graph *graph, int *ant, int i, int path_i)
{
	// int		ant_i[graph->ant_amount];
	// t_path	*tmp;

	// // i = 0;
	// tmp = path;
	// dprintf(g_fd, "L%d-%s ", ant + 1, graph->arr[tmp->path[i]]);
	// if (graph->ant_amount != 1 && ant < graph->p_num)
	// 	output(path->next, graph, ant + 1, i);
	while (*ant < graph->ant_amount)
	{
		graph->output[path_i][i] = 1;
		*ant += 1;
		dprintf(g_fd, "L%d-%s ", *ant, graph->arr[graph->p_arr[path_i][i]]);
		path_i++;
	}
}

void	go_ant_go(t_graph *graph)
{
	int		ant[2];
	int		i;
	int		path_i[2];

	i = 0;
	ant[0] = 0;
	path_i[0] = 0;
	while (ant[1] < graph->ant_amount)
	{
		ant[0] = ant[1];
		path_i[0] = path_i[1];
		while (path_i[0] < graph->p_num)
		{
			graph->output[path_i[0]][i] = 1;
			dprintf(g_fd, "L%d-%s ", ant[0] + 1, graph->arr[graph->p_arr[path_i[0]][i]]);
			if (graph->p_arr[path_i[0]][i + 1] == -1)
			{
				path_i[1] = path_i[0] + 1;
				ant[1] = ant[0] + 1;
			}
			path_i[0]++;
			ant[0]++;
		}
		if (ant[0] == graph->p_num && i > 0 && ant[0] < graph->ant_amount)
		{
			output(graph, &ant[0], i - 1, path_i[1]);
		}
		i++;
		dprintf(g_fd, "\n");
	}

	// while (ant <= graph->ant_amount)
	// {
	// 	path_i += 1;
	// 	// if (graph->p_arr[path_i - 1][i + 1] == -1)
	// 	// 	break ;
	// 	if (path_i == graph->p_num || graph->ant_amount == 1)
	// 	{
	// 		path_i = 0;
	// 		while (ant < graph->ant_amount && i > 0)
	// 		{
	// 			output(graph, &ant, i - 1, path_i);
	// 		}
	// 		dprintf(g_fd, "\n");
	// 		ant = 1;
	// 		i += 1;
	// 	}
	// 	else
	// 		ant++;
	// 	while (graph->p_arr[path_i][i] == graph->end_room)
	// 	{
	// 		path_i += 1;
	// 		ant++;
	// 	}
	// }
}

void	algorithm(t_graph *graph)
{
	t_path	*variant;
	t_link	*path;
	int		*arr;
	int		i;
	int		k;

	path = NULL;
	variant = NULL;
	dprintf(g_fd, "ant_amount = %d\n", graph->ant_amount);
	dprintf(g_fd, "end = %d\n", graph->end_room);
	dprintf(g_fd, "rooms = %d\n", graph->rooms);
	k = 0;
	i = create_start_matrix(graph);
	arr = (int *)ft_memalloc(sizeof(int) * graph->rooms);
	while (k < i)
	{
		add_link(&path, graph->starts[k]);
		match_column(graph->links, graph->starts[k], graph->rooms);
		deeper(variant, graph, &path, graph->starts[k]);
		clear_link(&path);
		// dprintf(g_fd, "\n *** j = %d ***\n", j);
		unmatch(graph, k);
		k++;
	}
	sort_path(graph->pathes);
	define_right_variants(graph, arr);
	make_arrays(graph);
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	go_ant_go(graph);
	free(arr);
}
