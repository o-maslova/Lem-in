#include "lem_in.h"

void	print_arr(t_graph *graph)
{
	int i;

	i = 0;
	while (i < graph->rooms)
	{
		dprintf(g_fd, "%d ", graph->v_arr[i++]); 
	}
	dprintf(g_fd, "\n");
}
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
		if (graph->links[i][k] == 1 && i != END && k != END)
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

int		out_it_2(t_graph *graph, int ant, int lim)
{
	// int		j;
	int		done_with;
	int		that_ant;
	t_path	*tmp;
	
	done_with = 0;
	// lim = lim > graph->p_num ? lim - graph->p_num : 0;
	that_ant = lim + 1;
	while (that_ant <= ant)
	{
		tmp = graph->pathes;
		// while (tmp && lim-- > 0)
		// 	tmp = tmp->next;
		while (tmp && that_ant <= ant)
		{
			// j = tmp->j;
			// if (that_ant > tmp->ant)
			// 	tmp = tmp->next;
			if (tmp && tmp->path[tmp->j] < 0)
			{
				tmp->path[tmp->j] = -tmp->path[tmp->j];
				if (tmp->path[tmp->j] == graph->end_room)
					done_with++;
				dprintf(g_fd, "L%d-%s ", that_ant, graph->arr[tmp->path[tmp->j]]);
				that_ant++;
			}
			tmp->j -= 1;
			tmp = tmp->next;
		}
	}
	dprintf(g_fd, "\n");
	return (done_with);
}

void	match_rooms(t_path *path, int i, int ant)
{
	int		j;
	t_path	*tmp;

	tmp = path;
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
	int		done_with;
	t_path	*tmp;

	ant = 0;
	done_with = 0;
	while (done_with < graph->ant_amount)
	{
		tmp = graph->pathes;
		while (tmp)
		{
			if (tmp->i > 0 && graph->ant_amount > graph->p_num)
				match_rooms(tmp, tmp->i, ant);
			if (tmp->i < tmp->p_val)
				tmp->path[tmp->i] = -tmp->path[tmp->i];
			if (ant < graph->ant_amount)
				ant++;
			// if (tmp->path[0] < 0)
			// 	ant++;
			tmp->j = tmp->i;
			if (tmp->i < tmp->p_val - 1)
				tmp->i += 1;
			tmp = tmp->next;
		}
		done_with += out_it_2(graph, ant, done_with);
	}
}

// void	initial(t_graph *graph, t_algo *algo_stuff)
// {
// 	int i;

// 	i = 0;
// 	algo_stuff->distances = (int *)ft_memalloc(sizeof(int) * ROOMS);
// 	algo_stuff->prev = (int *)ft_memalloc(sizeof(int) * ROOMS);
// 	algo_stuff->visited = (int *)ft_memalloc(sizeof(int) * ROOMS);
// 	algo_stuff->used = (int *)ft_memalloc(sizeof(int) * ROOMS);
// 	while (i < ROOMS)
// 	{
// 		algo_stuff->distances[i] = -1;
// 		algo_stuff->prev[i] = 0;
// 		algo_stuff->visited[i] = 0;
// 		algo_stuff->used[i] = 0;
// 		i++;
// 	}
// 	algo_stuff->queue = (t_queue *)ft_memalloc(sizeof(t_queue));
// 	algo_stuff->queue->start = (t_link *)ft_memalloc(sizeof(t_link));
// 	algo_stuff->queue->end = algo_stuff->queue->start;
// 	algo_stuff->queue->start->pos = graph->graph->pos;
// 	algo_stuff->queue->start->next = NULL;
// 	algo_stuff->used[0] = 1;
// 	algo_stuff->distances[0] = 0;
// }

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

// int		deeper(int room, t_graph *graph, t_algo *algo_stuff)
// {
// 	int i;

// 	i = 0;
// 	while (i < ROOMS)
// 	{
// 		if (graph->links[room][i] == 1 && algo_stuff->visited[i] == 0)
// 		{
// 			algo_stuff->distances[i] = algo_stuff->distances[room] + 1;
// 			algo_stuff->prev[i] = room;
// 			algo_stuff->visited[i] = 1;
// 			put_to_queue(algo_stuff->queue, room);
// 			if (i == END)
// 				return (1);
// 		}
// 		i++;
// 	}
// 	return (0);
// }

void	delete(t_algo *algo_stuff)
{
	t_link *fr;
	t_link *tmp;

	free(algo_stuff->visited);
	free(algo_stuff->distances);
	free(algo_stuff->prev);
	fr = algo_stuff->queue->start;
	while (fr)
	{
		tmp = fr->next;
		free(fr);
		fr = tmp;
	}
	free(algo_stuff->queue);
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
	// define_right_variants(graph, arr);
	// if (graph->ant_amount == 1)
	// 	clear_path(&(graph->pathes->next));
	// else
	define_right_variants(graph, arr);
	make_name_arr(graph);
	define_ant_and_path(graph);
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	// another_try_2(graph);
	free(arr);
}
