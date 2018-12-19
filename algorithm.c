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

int			check_path(t_link *path, int amount)
{
	int		check;
	t_link	*tmp;

	check = 0;
	tmp = path;
	while (tmp)
	{
		if (tmp->pos == amount)
			check = 1;
		tmp = tmp->next;
	}
	return (check);
}

void		match_visited(int **links, int i, int order, int amount)
{
	int k;

	k = 0;
	if (order == 1)
	{
		while (k < amount)
		{
			if (links[k][i] == 1)
				links[k][i] = -1;
			k++;
		}
	}
	else if (order == 2)
	{
		while (k < amount)
		{
			if (links[i][k] == 1)
				links[i][k] = -1;
			k++;
		}
	}
}

void		remove_part(t_link **path, int pos)
{
	t_link *fr;
	t_link *tmp;
	t_link *tmp_2;

	tmp = *path;
	while (tmp && tmp->pos != pos)
	{
		tmp = tmp->next;
		tmp_2 = tmp;
	}
	if (tmp)
	{
		tmp = tmp->next;
		while (tmp)
		{
			fr = tmp->next;
			free(tmp);
			tmp = fr;
		}
	}
	if (tmp_2 && tmp_2->next)
		tmp_2->next = NULL;
}

int			count_match(int *links, int amount)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < amount)
	{
		if (links[i] == 1)
			count++;
		i++;
	}
	return (count);
}

void		deeper(t_path **list, t_graph *graph, t_link **path, int i)
{
	static int		pos;
	t_path			*variant;
	int				check;
	int				k;

	k = 0;
	check = 0;
	while (++k < graph->rooms)
	{
		if (graph->links[i][graph->end_room] == 1)
		{
			add_link(path, graph->end_room);
			// match_visited(links, i, 1);
			match_visited(graph->links, i, 2, graph->rooms);
			variant = create_path(*path);
			// dprintf(g_fd,"NEW_PATH\n");
			// print_path(*path);
			add_path(list, variant);
			remove_part(path, pos);
			break ;
		}
		if (graph->links[i][k] == 1)
		{
			add_link(path, k);
			match_visited(graph->links, k, 1, graph->rooms);
			check = count_match(graph->links[k], graph->rooms);
			if (check > 1)
			{
				pos = k;
				deeper(list, graph, path, k);
			}
			if (check == 0)
			{
				remove_part(path, pos);
				continue ;
			}
			i = k;
			k = 0;
		}
	}
	// dprintf(g_fd,"\n");
	print_matrix(g_fd, graph);
}

void		algorithm(t_graph *graph)
{
	t_path	*list;
	t_link	*path;
	int		i;
	int		j;

	list = NULL;
	path = NULL;
	j = 0;
	i = count_match(graph->links[j], graph->rooms);
	dprintf(g_fd, "ant_amount = %d\n", graph->ant_amount);
	dprintf(g_fd, "end = %d\n", graph->end_room);
	dprintf(g_fd, "rooms = %d\n", graph->rooms);
	while (i > 0)
	{
		j = 0;
		while (graph->links[0][j] != 1 && j < graph->rooms)
			j++;
		add_link(&path, j);
		match_visited(graph->links, j, 1, graph->rooms);
		deeper(&list, graph, &path, j);
		clear_link(&path);
		i--;
	}
	print_variants(g_fd, list);
	clear_path(&list);
	// clear_matrix(graph->links, graph->rooms);
}
