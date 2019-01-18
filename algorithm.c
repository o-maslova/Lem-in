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

// void	out_it(t_graph *graph, int *ant, int k, int step, int *flag)
// {
// 	int i;
// 	int j;
// 	int add;

// 	i = step;
// 	j = 0;
// 	add = 1;
// 	while (i > 0)
// 	{
// 		if (k - step >= 0)
// 			dprintf(g_fd, "L%d-%s ", graph->ant_p[*ant][0], graph->arr[graph->ant_p[*ant][k - step]]);
// 		if (graph->ant_p[*ant][k - step] == graph->end_room)
// 		{
// 			graph->ant_p[*ant][k - step] = -graph->ant_p[*ant][k - step];
// 			*flag = *ant;
// 		}
// 		*ant += 1;
// 		j++;
// 		i--;
// 	}
// }

int		out_it_2(t_graph *graph, int k, int ant, int lim)
{
	int		j;
	int		done_with;
	int		that_ant;
	t_path	*tmp;
	
	j = k;
	done_with = 0;
	// lim = lim > graph->p_num ? lim - graph->p_num : 0;
	that_ant = lim + 1;
	while (that_ant <= ant)
	{
		tmp = graph->pathes;
		while (tmp && lim-- > 0)
			tmp = tmp->next;
		while (tmp && that_ant <= ant)
		{
			if (tmp->path[j] < 0)
			{
				tmp->path[j] = -tmp->path[j];
				if (tmp->path[j] == graph->end_room)
					done_with++;
				dprintf(g_fd, "L%d-%s ", that_ant, graph->arr[tmp->path[j]]);
			}
			tmp = tmp->next;
			that_ant++;
		}
		j--;
	}
	dprintf(g_fd, "\n");
	return (done_with);
}

void	match_rooms(t_path *path, int step, int i, int ant)
{
	int		j;
	t_path	*tmp;

	tmp = path;
	if (i < step)
		j = 0;
	else if (path->ant < ant)
		j = ant - path->ant;
	else
		j = i - step;
	while (j < path->p_val && j < i)
	{
		path->path[j] = -path->path[j];
		j++;
	}
}

void	another_try_2(t_graph *graph)
{
	int		i;
	int		ant;
	int		step;
	int		done_with;
	t_path	*tmp;

	ant = 0;
	i = 0;
	done_with = 0;
	step = define_step(graph->p_num, graph->ant_amount);
	while (done_with < graph->ant_amount)
	{
		tmp = graph->pathes;
		while (tmp)
		{
			if (i > 0 && graph->ant_amount > graph->p_num)
				match_rooms(tmp, step, i, ant);
			if (i < tmp->p_val)
				tmp->path[i] = -tmp->path[i];
			if (tmp->path[0] < 0)
				ant++;
			tmp = tmp->next;
		}
		done_with += out_it_2(graph, i, ant, done_with);
		i++;
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
	// if (graph->ant_amount == 1)
	// 	clear_path(&(graph->pathes->next));
	// else
		define_right_variants(graph, arr);
	make_name_arr(graph);
	// make_path_arr(graph);
	define_ant_and_path(graph);
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	another_try_2(graph);
	free(arr);
}
