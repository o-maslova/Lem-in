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

void		unmatch(int **links, int limit, int amount)
{
	int		i;
	int		j;

	i = 0;
	while (i < amount)
	{
		j = 0;
		while (j < amount)
		{
			if (links[i][j] == -1 && j != limit)
				links[i][j] = 1;
			j++;
		}
		i++;
	}
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
	if (tmp_2 && tmp_2->next != NULL)
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

void		deeper(t_path **list, t_graph graph, t_link **path, int i)
{
	static int		pos;
	t_path			*variant;
	int				check;
	int				k;

	k = 0;
	check = 0;
	while (++k < graph.rooms)
	{
		if (graph.links[i][graph.end_room] == 1)
		{
			add_link(path, graph.end_room);
			variant = create_path(*path);
			dprintf(g_fd,"NEW_PATH\n");
			print_path(*path);
			add_path(list, variant);
			// clear_link(path);
			print_matrix(g_fd, graph);
			dprintf(g_fd, "\n");
			remove_part(path, (*path)->pos);
			break ;
		}
		if (graph.links[i][k] == 1)
		{
			add_link(path, k);
			graph.links[i][k] = -1;
			graph.links[k][i] = -1;
			check = count_match(graph.links[k], graph.rooms);
			if (check >= 1)
			{
				pos = i;
				deeper(list, graph, path, k);
			}
			if (check == 0)
			{
				remove_part(path, pos);
				// continue ;
			}
			// i = k;
			// k = 0;
		}
	}
	// if (k == graph->rooms)
	// {
	// 	remove_part(path, &pos);
	// 	deeper(list, graph, path, pos);
	// }
	// }
	// k = pos;
}

void		create_dup_matrix(t_graph *graph)
{
	int i;
	int j;
	int k;

	i = 0;
	graph->arr = (int **)ft_memalloc(sizeof(int *) * graph->rooms);
	while (i < graph->rooms)
	{
		k = count_match(graph->links[i], graph->rooms);
		graph->arr[i] = (int *)ft_memalloc(sizeof(int) * (k + 1));
		k = 0;
		j = 0;
		while (j < graph->rooms)
		{
			if (graph->links[i][j] == 1)
			{
				if (j != graph->rooms - 1)
					graph->links[j][i] = -1;
				graph->arr[i][k++] = j;
			}
			j++;
		}
		graph->arr[i][k++] = -1;
		i++;
	}
	printf_this(graph->arr, graph->rooms);
}

void		algo(t_graph *graph, t_link **path, int i)
{
	int j;

	j = 0;
	while (graph->arr[i][j] != -1)
	{
		if (graph->arr[i][j] == i)
			break ;
		add_link(path, graph->arr[i][j]);
		graph->arr[i][j] = -1;
		algo(graph, path, graph->arr[i][j++]);

		// graph->links[graph->arr[i][j]][graph->arr[i][j]]
	}
	// if (graph->arr[i][j] == -1)
	
}

void		algorithm(t_graph graph)
{
	t_path	*list;
	t_link	*path;
	int		i;
	int		j;

	list = NULL;
	path = NULL;
	j = 0;
	i = count_match(graph.links[j], graph.rooms);
	dprintf(g_fd, "ant_amount = %d\n", graph.ant_amount);
	dprintf(g_fd, "end = %d\n", graph.end_room);
	dprintf(g_fd, "rooms = %d\n", graph.rooms);
	// create_dup_matrix(graph.
	while (i > 0)
	{
		j = 0;
		while (graph.links[0][j] != 1 && j < graph.rooms)
			j++;
		add_link(&path, j);
		match(graph.links, j, graph.rooms);
		deeper(&list, graph, &path, j);
		unmatch(graph.links, j, graph.rooms);
		clear_link(&path);
		i--;
	}
	// print_variants(g_fd, list);
	clear_path(&list);
	// clear_matrix(graph.links, graph.rooms);
}
