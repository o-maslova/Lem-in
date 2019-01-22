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

int		deeper(t_graph *graph, t_link *path, int i)
{
	int		k;
	int		j;
	int		count;

	k = i;
	count = 1;
	while (k < graph->rooms)
	{
		j = 0;
		while (j < graph->rooms)
		{
			if (graph->links[k][graph->end_room] == 1)
			{
				add_link(&path, graph->end_room);
				return (++count);
			}
			if (graph->links[k][j] == 1 && graph->v_arr[j] > 0)
			{
				add_link(&path, graph->v_arr[j]);
				graph->v_arr[j] = -graph->v_arr[j];
				count++;
				k = --j;
				break;
			}
			j++;
		}
		k++;
	}
	return (count);
	// while (++k < graph->rooms)
	// {
	// 	if (graph->links[i][graph->end_room] == 1)
	// 	{
	// 		add_link(path, graph->end_room);
	// 		variant = create_path(*path);
	// 		add_path(&(graph->pathes), variant);
	// 		return (1);
	// 	}
	// 	if (graph->links[i][k] == 1)
	// 	{
	// 		add_link(path, k);
	// 		graph->links[i][k] = -1;
	// 		graph->links[k][i] = -1;
	// 		if ((deeper(variant, graph, path, k)) == 1)
	// 			remove_part(path, k);
	// 		else
	// 		{
	// 			remove_last(path);
	// 			// graph->links[i][k] = 0;
	// 			// graph->links[k][i] = 0;
	// 		}
	// 	}
	// }
	// free(variant);
	// return (0);
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

int		out_it_2(t_graph *graph, int ant, int lim)
{
	int		done_with;
	int		that_ant;
	int		counter1;
	int		counter2;
	t_path	*tmp;
	
	counter1 = 0;
	counter2 = 0;
	done_with = 0;
	that_ant = lim;
	while ((that_ant < ant || done_with < graph->p_num) && counter1 <= done_with) //(counter < graph->p_num || done_with < graph->p_num))
	{
		tmp = graph->pathes;
		while (tmp && lim > 0)
		{
			tmp = tmp->next;
			lim--;
		}
		while (tmp && that_ant < ant)
		{
			if (tmp && tmp->path[tmp->j] < 0)
			{
				tmp->path[tmp->j] = -tmp->path[tmp->j];
				if (tmp->path[tmp->j] == graph->end_room)
					done_with++;
				dprintf(g_fd, "L%d-%s ", that_ant + 1, graph->arr[tmp->path[tmp->j]]);
				// dprintf(g_fd, "(tmp->j = %d, that_ant #%d, ant %d)", tmp->j, that_ant, ant);
				that_ant++;
				if (tmp->j == tmp->k)
				{
					counter1++;
				}
				if (tmp->j <= tmp->k && tmp->j == 0)
					counter2++;
			}
			tmp->j = tmp->j > 0 ? tmp->j - 1 : tmp->j;
			// counter = tmp->j - 1 == 0 ? counter + 1 : counter;
			tmp = tmp->next;
		}
		// if (counter == done_with && counter > 0)
		// 	break ;
	}
	dprintf(g_fd, "\n");
	return (done_with);
}

void	match_rooms(t_path *path, int step, int i, int ant)
{
	int		j;
	t_path	*tmp;

	tmp = path;
	step = 0;
	if (ant <= path->ant)
		j = 0;
	else
		j = (path->k)++;
	while (j < path->p_val && j < i)
	{
		path->path[j] = -path->path[j];
		j++;
	}
}

void	another_try_2(t_graph *graph)
{
	int		ant;
	int		step;
	int		done_with;
	t_path	*tmp;

	ant = 0;
	done_with = 0;
	step = define_step(graph->p_num, graph->ant_amount);
	while (done_with < graph->ant_amount)
	{
		tmp = graph->pathes;
		while (tmp)
		{
			if (tmp->i > 0 && graph->ant_amount > graph->p_num)
				match_rooms(tmp, step, tmp->i, ant);
			if (tmp->i < tmp->p_val)
				tmp->path[tmp->i] = -tmp->path[tmp->i];
			if (ant < graph->ant_amount)
				ant++;
			tmp->j = tmp->i;
			if (tmp->i < tmp->p_val - 1)
				tmp->i += 1;
			tmp = tmp->next;
		}
		done_with += out_it_2(graph, ant, done_with);
	}
}

int		*create_arr(t_graph *graph)
{
	int		i;
	int		*v_arr;
	t_vert	*tmp;

	i = 0;
	tmp = graph->graph;
	v_arr = (int *)ft_memalloc(sizeof(int) * graph->rooms);
	while (i < graph->rooms)
	{
		v_arr[i++] = tmp->pos;
		tmp = tmp->next;
	}
	return (v_arr);
}

void	match_vert(t_graph *graph, t_link *path, int val)
{
	int		i;
	// t_link	*path;
	t_path	*variant;
	// int result;

	i = 0;
	// result = 0;
	variant = NULL;
	while (i < graph->rooms)
	{
		if (graph->v_arr[i] < 0)
		{
			add_link(&path, -graph->v_arr[i]);
			graph->v_arr[i] = 0;
			// result++;
		}
		// if (graph->v_arr[i] == graph->end_room)
		// 	add_link(&path, graph->v_arr[i]);
		i++;
	}
	add_link(&path, graph->v_arr[graph->end_room]);
	variant = create_path(path, val);
	add_path(&(graph->pathes), variant);
	// clear_link(&path);
	// free(variant);
}

void	algorithm(t_graph *graph)
{
	t_path	*variant;
	t_link	*path;
	// int		i;
	int		k;
	int		p_value;

	path = NULL;
	variant = NULL;
	dprintf(g_fd, "ant_amount = %d\n", graph->ant_amount);
	dprintf(g_fd, "end = %d\n", graph->end_room);
	dprintf(g_fd, "rooms = %d\n", graph->rooms);
	k = 0;
	// i = create_start_matrix(graph);
	graph->v_arr = create_arr(graph);
	while (k < graph->rooms)
	{
		if (graph->links[0][k] == 1)
		{
			add_link(&path, k);
			graph->v_arr[k] = -graph->v_arr[k];
			p_value = deeper(graph, path, k);
			variant = create_path(path, p_value);
			add_path(&(graph->pathes), variant);
			// match_vert(graph, path, p_value);
			clear_link(&path);
			// free(variant);
		}
		k++;
	}
	// while (k < i)
	// {
	// 	add_link(&path, graph->starts[k]);
	// 	// match_column(graph->links, graph->starts[k], graph->rooms);
	// 	deeper(variant, graph, &path, graph->starts[k]);
	// 	// clear_link(&path);
	// 	// print_matrix(g_fd, *graph);
	// 	// dprintf(g_fd, "\n");
	// 	// unmatch(graph, k);
	// 	k++;
	// }
	sort_path(graph->pathes);
	// define_right_variants(graph, arr);
	print_variants(g_fd, graph->pathes);
	make_name_arr(graph);
	graph->pathes->ant = graph->ant_amount;
	// define_ant_and_path(graph);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	// another_try_2(graph);
	// free(arr);
}
