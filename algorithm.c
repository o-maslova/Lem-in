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

void	out_it(t_graph *graph, int lim)
{
	int		i;
	int		flag;
	t_path	*tmp;

	i = lim;
	flag = 0;
	while (i >= 0)
	{
		tmp = graph->pathes;
		while (tmp)
		{
			while (tmp && tmp->p_val <= i)
				tmp = tmp->next;
			if (tmp && tmp->path[i][0] < 0)
			{
				tmp->path[i][0] = -tmp->path[i][0];
				dprintf(g_fd, "L%d-%s ", tmp->path[i][1], graph->arr[tmp->path[i][0]]);
			}
			if (flag)
				i = lim;
			if (tmp)
				tmp = tmp->next;
		}
		i--;
	}
}

void	go_ant_go(t_graph *graph)
{
	int		i;
	int		p_num;
	int		ants;
	t_path	*tmp;

	i = 0;
	ants = 0;
	while (ants < graph->ant_amount)
	{
		p_num = graph->p_num;
		tmp = graph->pathes;
		while (tmp && ants < graph->ant_amount && p_num > 0)
		{
			while (tmp && i >= tmp->p_val)
			{
				// if (graph->ant_amount == 1)
				// 	break ;
				tmp = tmp->next;
				ants++;
			}
			if (!tmp)
				break ;
			tmp->path[i][0] = -tmp->path[i][0];
			tmp->path[i][1] = ants + 1;
			ants++;
			tmp = tmp->next;
			p_num--;
		}
		if (ants == graph->ant_amount) // вот тут ломается, когда все выведет и дойдкт до конца списка
		{
			ants = 0;
			i++;
			if (graph->ant_amount > graph->p_num) // из-за этого не работает, когда муравьев больше, чем путей
				continue ;
		}
		else if (ants > graph->ant_amount || ants == 0)
			break ;
		out_it(graph, i);
		dprintf(g_fd, "\n");
	}
	//надо попробовать перенести в массив
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
	define_ant_step(graph);
	make_arrays(graph);
	print_variants(g_fd, graph->pathes);
	dprintf(g_fd, "p_num = %d\n", graph->p_num);
	go_ant_go(graph);
	free(arr);
}
