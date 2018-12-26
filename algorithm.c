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

void		match(int **links, int k, int amount)
{
	int i;

	i = 0;
	while (i < amount)
	{
		links[i][k] = -1;
		i++;
	}
}

void		unmatch(t_graph graph, int limit)
{
	int		k;
	int		i;
	int		j;

	i = 0;
	while (i < graph.rooms)
	{
		j = 0;
		k = 0;
		while (j < graph.rooms)
		{
			if (graph.links[i][j] == -1)
			{
				if (j == graph.starts[k] && k <= limit)
				{
					k++;
				}
				else
					graph.links[i][j] = 1;
			}
			j++;
		}
		i++;
	}
}

void		remove_last(t_link **path)
{
	t_link *tmp;

	if (!(*path))
		return ;
	tmp = *path;
	while (tmp->next->next)
	{
		tmp = tmp->next;
	}
	free(tmp->next->next);
	tmp->next = NULL;
}

void		remove_part(t_link **path, int pos)
{
	t_link *fr;
	t_link *tmp;
	t_link *tmp_2;

	// tmp_2 = NULL;
	// if (!(*path))
	// 	return ;
	// tmp = *path;
	// while (tmp && tmp->next)
	// {
	// 	if (tmp->next->pos == *pos)
	// 		break ;
	// 	tmp = tmp->next;
	// 	tmp_2 = tmp;
	// }
	// if (tmp)
	// {
	// 	tmp = tmp->next->next;
	// 	while (tmp)
	// 	{
	// 		fr = tmp->next;
	// 		free(tmp);
	// 		tmp = fr;
	// 	}
	// }
	// if ((*path)->next->next && tmp_2)
	// {
	// 	if (tmp_2->next && tmp_2->next->next)
	// 	{
	// 		tmp_2->next->next = NULL;
	// 		*pos = tmp_2->next->pos;
	// 	}
	// 	else if (tmp_2->next)
	// 	{
	// 		free(tmp_2->next);
	// 		tmp_2->next = NULL;
	// 		*pos = tmp_2->pos;
	// 	}
	// }
	tmp = *path;
	tmp_2 = NULL;
	if (tmp->pos == pos)
	{
		clear_link(&(*path)->next);
		return ;
	}
	while (tmp && tmp->pos != pos)
	{
		tmp_2 = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		// tmp = tmp->next;
		while (tmp)
		{
			fr = tmp->next;
			free(tmp);
			tmp = fr;
		}
	}
	// if (tmp_2 && tmp_2->next != NULL)
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

int		deeper(t_path **list, t_graph graph, t_link **path, int i)
{
	t_path	*variant;
	int		k;

	k = 0;
	while (++k < graph.rooms)
	{
		if (graph.links[i][graph.end_room] == 1)
		{
			add_link(path, graph.end_room);
			variant = create_path(*path);
			add_path(list, variant);
			return (1);
		}
		if (graph.links[i][k] == 1)
		{
			add_link(path, k);
			graph.links[i][k] = -1;
			graph.links[k][i] = -1;
			if ((deeper(list, graph, path, k)) == 1)
			{
				// dprintf(g_fd, "remove part\n");
				remove_part(path, k);
			}
			else
			{
				// dprintf(g_fd, "remove last\n");
				remove_last(path);
			}
		}
	}
	return (0);
}

int		create_start_matrix(t_graph *graph)
{
	int i;
	int j;

	i = count_match(graph->links[0], graph->rooms);
	graph->starts = (int *)ft_memalloc(sizeof(int) * (i + 1));
	i = 0;
	j = 0;
	while (j < graph->rooms)
	{
		if (graph->links[0][j] == 1)
		{
			// if (j != graph->rooms - 1)
			// 	graph->links[j][i] = -1;
			graph->starts[i++] = j;
		}
		j++;
	}
	graph->starts[i] = -1;
	printf_this(graph->starts);
	return (i);
}

void		algorithm(t_graph graph)
{
	t_path	**list;
	t_link	*path;
	int		i;
	int		j;
	int		k;

	list = NULL;
	path = NULL;
	dprintf(g_fd, "ant_amount = %d\n", graph.ant_amount);
	dprintf(g_fd, "end = %d\n", graph.end_room);
	dprintf(g_fd, "rooms = %d\n", graph.rooms);
	k = 0;
	i = create_start_matrix(&graph);
	list = (t_path **)ft_memalloc(sizeof(t_path *) * i);
	while (k < i)
	{
		add_link(&path, graph.starts[k]);
		match(graph.links, graph.starts[k], graph.rooms);
		j = deeper(&(list[k]), graph, &path, graph.starts[k]);
		clear_link(&path);
		list[k] = sort_path(list[k]);
		dprintf(g_fd, "\n *** j = %d ***\n", j);;
		print_variants(g_fd, list[k], k + 1);
		unmatch(graph, k);
		// print_matrix(g_fd, graph);
		k++;
	}
	// clear_path(&list);
	// clear_matrix(graph.links, graph.rooms);
}
