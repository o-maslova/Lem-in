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

int		found_match(t_path *tmp, int *arr, int end)
{
	int		k;
	int		i;

	i = 0;
	k = 0;
	while (i < tmp->path_val)
	{
		if (arr[tmp->path[i]] == 0 && tmp->path[i] != end)
			k++;
		i++;
	}
	return (k);
}

void	define_right_variants(t_graph *graph, int *arr)
{
	int		k;
	t_path	*prev;
	t_path	*tmp;
	t_path	*fr;

	tmp = graph->pathes;
	while (tmp)
	{
		k = found_match(tmp, arr, graph->end_room);
		if (k + 1 == tmp->path_val)
		{
			match(arr, tmp->path, tmp->path_val);
			prev = tmp;
			graph->pathes_num += 1;
		}
		else
		{
			fr = tmp->next;
			free(tmp);
			prev->next = fr;
		}
		tmp = tmp->next;
	}
}

int		create_start_matrix(t_graph *graph)
{
	int i;
	int j;
	int count;

	i = 0;
	count = 0;
	while (i < graph->rooms)
	{
		if (graph->links[0][i] == 1)
			count++;
		i++;
	}
	graph->starts = (int *)ft_memalloc(sizeof(int) * (count + 1));
	i = 0;
	j = 0;
	while (j < graph->rooms)
	{
		if (graph->links[0][j] == 1)
			graph->starts[i++] = j;
		j++;
	}
	graph->starts[i] = -1;
	printf_this(graph->starts);
	return (i);
}

void	arr_memalloc(int **arr, int amount, t_path *pathes)
{
	int		i;
	t_path	*tmp;

	i = 0;
	tmp = pathes;
	arr = (int **)ft_memalloc(sizeof(int *) * amount);
	while (i < amount)
	{
		arr[i] = (int *)ft_memalloc(sizeof(int) * tmp->path_val);
		tmp = tmp->next;
		i++;
	}
}

void	output(t_path *path, int ant, int i, int amount)
{
	dprintf(g_fd, "L%d-%d\n", ant, path->path[i]);
	if (amount > 1)
	{
		path = path->next;
		ant += 1;
	}
	
	while (path->path[i] != -1)
	{
		if (ant < amount)
		{
			output(path, ant, i + 1, amount);
		}
	}
	// ant = 0;
	// i++;
}

void	go_ant_go(t_graph *graph)
{
	int		ant;
	int		path_i;
	int		**arr;
	// int		index[graph->ant_amount];
	t_path	*tmp;

	ant = 0;
	path_i = 0;
	tmp = graph->pathes;
	arr = NULL;
	// arr_memalloc(arr, graph->pathes_num, graph->pathes);
	output(tmp, ant, path_i, graph->ant_amount);
	// while (ant < graph->ant_amount)
	// {
	// 	while (tmp->path[path_i] != -1)
	// 	{
	// 		// dprintf(g_fd, "L%d-%d\n", ant + 1, tmp->path[path_i]);
	// 		dprintf(g_fd, "L%d-%s\n", ant + 1, search_by_pos(graph, tmp->path[path_i]));
	// 		path_i++;
	// 	}
	// 	ant++;
	// 	tmp = tmp->next;
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
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "num = %d\n", graph->pathes_num);
	go_ant_go(graph);
	free(arr);
}
