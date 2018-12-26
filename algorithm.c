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

// void	go_ant_go(t_graph *graph);
// {
// 	int		i;
// 	int		j;
// 	t_path	*tmp;

// 	i = 0;
// 	tmp = graph->pathes;
// 	while (i < graph->ant_amount && i < graph->pathes_num)
// 	{
// 		dprintf(g_fd, "L%d-%d", i, tmp->path[0]);
// 		i++;
// 		tmp = tmp->next;
// 	}
// 	if ()
// 	j = 0;
// 		while (tmp)
// 		{
// 		}
// 	}
// }

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
		// dprintf(g_fd, "\n *** j = %d ***\n", j);;
		unmatch(graph, k);
		k++;
	}
	sort_path(graph->pathes);
	define_right_variants(graph, arr);
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "num = %d\n", graph->pathes_num);
	// go_ant_go(graph);
	free(arr);
}
