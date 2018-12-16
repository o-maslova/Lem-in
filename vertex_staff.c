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

int			**memory_allocate(int *check)
{
	int i;
	int **tmp;

	i = 0;
	*check += 1;
	g_amount += 1;
	tmp = (int **)ft_memalloc(sizeof(int *) * g_amount);
	while (i < g_amount)
	{
		tmp[i] = (int *)ft_memalloc(sizeof(int) * g_amount);
		i++;
	}
	return (tmp);
}

t_vert		*vertex_create(char **arr, int pos)
{
	static int	i;
	t_vert		*vrt;

	vrt = NULL;
	if (arr)
	{
		vrt = (t_vert *)ft_memalloc(sizeof(t_vert));
		vrt->name = ft_strdup(arr[0]);
		vrt->x = ft_atoi(arr[1]);
		vrt->y = ft_atoi(arr[2]);
		vrt->is_start = pos == 1 ? 1 : 0;
		vrt->is_end = pos == 2 ? 1 : 0;
		if (vrt->is_start)
			vrt->pos = 0;
		else
			vrt->pos = ++i;
		g_amount = vrt->pos;
		vrt->next = NULL;
	}
	return (vrt);
}

void		add_vertex(t_vert **graph, t_vert *new)
{
	t_vert		*tmp;

	tmp = NULL;
	if (!(*graph) && new)
		*graph = new;
	else if (new->is_start)
	{
		new->next = *graph;
		*graph = new;
	}
	else
	{
		tmp = *graph;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = new;
	}
}
