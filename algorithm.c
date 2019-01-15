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

int		define_step(int p_num, int ants)
{
	int i;
	int step;

	i = p_num;
	step = 0;
	while (i < ants)
	{
		step++;
		i += p_num;
	}
	return (step);
}

void	out_it(t_graph *graph, int *ant, int k, int step, int *flag)
{
	int i;
	int j;
	int add;

	i = step;
	j = 0;
	add = 1;
	while (i > 0)
	{
		if (k - step >= 0)
			dprintf(g_fd, "L%d-%s ", graph->ant_p[*ant][0], graph->arr[graph->ant_p[*ant][k - step]]);
		if (graph->ant_p[*ant][k - step] == graph->end_room)
		{
			graph->ant_p[*ant][k - step] = -graph->ant_p[*ant][k - step];
			*flag = *ant;
		}
		*ant += 1;
		j++;
		i--;
	}
}

void	another_try(t_graph *graph)
{
	int		k;
	int		num;
	int		flag;
	int		ant;
	int		step;

	k = 1;
	num = 0;
	flag = 0;
	step = define_step(graph->p_num, graph->ant_amount);
	while (flag < graph->ant_amount)
	{
		ant = flag;
		while (ant < graph->p_num)
		{
			dprintf(g_fd, "L%d-%s ", graph->ant_p[ant][0], graph->arr[graph->ant_p[ant][k]]);
			if (graph->ant_p[ant][k] == graph->end_room)
			{
				graph->ant_p[ant][k] = graph->ant_p[ant][k] * -1;
				flag = ant + 1;
			}
			ant++;
		}
		if (step > 0 && k > 1)
			out_it(graph, &ant, k, step, &flag);
		k++;
		dprintf(g_fd, "\n");
	}
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
	// print_variants(g_fd, graph->pathes);
	define_right_variants(graph, arr);
	define_ant_and_path(graph);
	make_array(graph);
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	another_try(graph);
	free(arr);
}
