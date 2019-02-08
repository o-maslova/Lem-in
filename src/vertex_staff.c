/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   vertex_staff.c                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:07:35 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:07:36 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		memory_allocate(t_graph **graph, int *check)
{
	int i;
	int tmp;

	i = 0;
	*check += 1;
	(*graph)->rooms += 1;
	tmp = (*graph)->rooms;
	(*graph)->links = (int **)ft_memalloc(sizeof(int *) * tmp);
	while (i < tmp)
	{
		(*graph)->links[i] = (int *)ft_memalloc(sizeof(int) * tmp);
		i++;
	}
}

t_vert		*vertex_create(t_graph *graph, char **arr, int pos)
{
	static int	i;
	t_vert		*vrt;

	vrt = NULL;
	if (arr)
	{
		vrt = (t_vert *)malloc(sizeof(t_vert));
		vrt->name = ft_strdup(arr[0]);
		vrt->x = ft_atoi(arr[1]);
		vrt->y = ft_atoi(arr[2]);
		vrt->is_start = pos == 1 ? 1 : 0;
		vrt->is_end = pos == 2 ? 1 : 0;
		if (vrt->is_start)
			vrt->pos = 0;
		else
			vrt->pos = ++i;
		graph->rooms = vrt->pos > 0 ? vrt->pos : i + 1;
		vrt->next = NULL;
	}
	return (vrt);
}

int			check_vertex(t_vert *tmp, t_vert *new)
{
	int res;

	res = 0;
	if (ft_strcmp(tmp->name, new->name) == 0)
		res = 8;
	else if (tmp->x == new->x && tmp->y == new->y)
		res = 9;
	return (res);
}

void		add_vertex(t_graph **graph, t_vert **rooms, t_vert *new)
{
	int		res;
	t_vert	*tmp;

	tmp = NULL;
	if (!(*rooms) && new)
		*rooms = new;
	else if (new->is_start)
	{
		new->next = *rooms;
		*rooms = new;
	}
	else
	{
		tmp = *rooms;
		while (tmp->next)
		{
			if ((res = check_vertex(tmp, new)))
				error_handling(res, NULL, graph);
			(*graph)->is_neg = tmp->name[0] == '-' ? 1 : (*graph)->is_neg;
			tmp = tmp->next;
		}
		if ((res = check_vertex(tmp, new)))
			error_handling(res, NULL, graph);
		tmp->next = new;
	}
}

void		add_node(t_graph **graph, char **arr, int pos)
{
	t_vert *tmp;

	tmp = vertex_create(*graph, arr, pos);
	if (tmp->name[0] == 'L' || tmp->name[0] == '#')
	{
		free(tmp->name);
		free(tmp);
		error_handling(11, arr, graph);
	}
	if (pos == 2)
		(*graph)->end_room = tmp->pos;
	add_vertex(graph, &((*graph)->graph), tmp);
}
