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

void		output(t_path *path, t_graph *graph, int ant, int i)
{
	// // int		i;
	// t_path	*tmp;

	// // i = 0;
	// tmp = path;
	// dprintf(g_fd, "L%d-%s ", ant + 1, graph->arr[tmp->path[i]]);
	// if (graph->ant_amount != 1 && ant < graph->pathes_num)
	// 	output(path->next, graph, ant + 1, i);

	if (path)
	{
		if (path->path[i] == -1)
		{
			ant += 1;
			path = path->next;
		}
		if (path && ant <= graph->ant_amount)
		{
			dprintf(g_fd, "L%d-%s ", ant + 1, graph->arr[path->path[i]]);
			output(path->next, graph, ant + 1, i);
		}
		// else if (ant <= graph->ant_amount)
	}
	else if (ant == graph->pathes_num && ant < graph->ant_amount)
	{
		dprintf(g_fd, "\n");
		ant -= graph->pathes_num;
		output(graph->pathes, graph, ant, i + 1);
	}
	else if (ant < graph->ant_amount && ant > graph->pathes_num)
	{
		output(graph->pathes, graph, ant + 1, i);
	}
}

// int		**create_index_mtrx(t_path *path, int pathes_num)
// {
// 	int		i;
// 	int		*arr;
// 	t_path	*tmp;

// 	i = 0;
// 	arr = (int *)ft_memalloc(sizeof(int) * pathes_num);
// 	tmp = path;
// 	while (tmp)
// 	{
// 		arr[i++] = tmp->path_val;
// 		tmp = tmp->next;
// 	}
// }

void	go_ant_go(t_graph *graph)
{
	int		ant;
	// int		index[graph->pathes_num];
	int		i;
	int		j;
	t_path	*tmp;

	i = 0;
	j = 0;
	ant = 0;
	// index = create_index_mtrx(graph->pathes, graph->pathes_num);
	// while (ant < graph->ant_amount)
	// {
		
		tmp = graph->pathes;
		output(tmp, graph, ant, i);
		// // dprintf(g_fd, "\n");
		// while (ant < graph->pathes_num && graph->ant_amount != 1)
		// {
		// 	dprintf(g_fd, "L%d-%s ", ant + 1, graph->arr[tmp->path[i]]);
		// 	tmp = tmp->next;
		// 	ant++;
		// }
		// graph->pathes_num += graph->pathes_num;
		// i++;
		// ant += graph->pathes_num;
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
	make_arr(graph);
	// print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "pathes_num = %d\n", graph->pathes_num);
	go_ant_go(graph);
	free(arr);
}
