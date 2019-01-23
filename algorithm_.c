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

void	clear(t_algo *algo_stuff, int num)
{
	int i;

	i = 0;
	while (i < num)
	{
		algo_stuff->visited[i] = 0;
		algo_stuff->distances[i] = 0;
		algo_stuff->prev[i] = 0;
		i++;
	}
	// ft_bzero(algo_stuff->visited, num);
	// ft_bzero(algo_stuff->distances, num);
	// ft_bzero(algo_stuff->prev, num);
}

void	it_match(int *arr, int *used, int num)
{
	int		i;

	i = 0;
	while (i < num - 1)
	{
		used[arr[i]] = 1;
		i++;
	}
}

int		deeper(t_algo *algo, t_graph *graph, int *used, int i)
{
	t_path		*variant;
	static int	j;
	int			k;

	// while (i < ROOMS && i != END)
	// {
		k = 0;
		while (++k < ROOMS)
		{
			if (k != END && graph->links[i][END] == 1)
			{
				algo->visited[k] = 1;
				algo->prev[j++] = i;
				variant = create_path(graph, algo, j);
				add_path(&(graph->pathes), variant);
				// it_match(variant->path, used, variant->p_val);
				// algo->prev[--j] = 0;
				clear(algo, variant->p_val);
				j = 0;
				return (1);
			}
			if (k != END && graph->links[i][k] == 1 && algo->visited[k] == 0 && used[k] == 0)
				{
				// dprintf(g_fd, "i = %d, ", i);
				algo->visited[k] = 1;
				algo->prev[j++] = i;
				// i = k;
				// k = 0;
				deeper(algo, graph, used, k);
				algo->prev[--j] = 0;
					// break ;
				// else
				// algo->prev[j - 1] = 0;
					// graph->links[i][k] = -1;
				// 	break ;
				// }
				// else
				// {
					// used[k] = 1;
			}
		}
		// clear(algo, ROOMS);
		// i++;
		// used[i] = 1;
		// i = algo->prev[--j];
	// }
	// dprintf(g_fd, "\n");
	if (j != 0)
		return (0);
	return (1);
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


void	algorithm(t_graph *graph)
{
	t_path	*variant;
	t_link	*path;
	t_algo	*algo;
	int		*used;
	int		i;
	int		k;

	path = NULL;
	variant = NULL;
	algo = (t_algo *)ft_memalloc(sizeof(t_algo));
	algo->distances = (int *)ft_memalloc(sizeof(int) * ROOMS);
	algo->visited = (int *)ft_memalloc(sizeof(int) * ROOMS);
	algo->prev = (int *)ft_memalloc(sizeof(int) * ROOMS);
	dprintf(g_fd, "ant_amount = %d\n", graph->ant_amount);
	dprintf(g_fd, "end = %d\n", graph->end_room);
	dprintf(g_fd, "rooms = %d\n", graph->rooms);
	k = 0;
	// val = 1;

	algo->visited[0] = 1;
	algo->prev[0] = -1;

	i = create_start_matrix(graph);
	used = (int *)ft_memalloc(sizeof(int) * graph->rooms);
	graph->v_arr = create_arr(graph);
	while (k < i)
	{
		// val = graph->starts[k];
		algo->visited[graph->starts[k]] = 1;
		algo->prev[0] = graph->starts[k];
		deeper(algo, graph, used, graph->starts[k]);
		used[graph->starts[k]] = 1;
		// dprintf(g_fd, "\n *** j = %d ***\n", j);
		// unmatch(graph, k);
		k++;
	}
	sort_path(graph->pathes);
	// define_right_variants(graph, used);
	make_name_arr(graph);
	graph->pathes->ant = graph->ant_amount;
	// define_ant_and_path(graph);
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	// another_try_2(graph);
}