/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   path_staff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:07:51 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:07:54 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void		swap_values(t_path *tmp, t_path *first, t_path *second)
{
	tmp->path = first->path;
	tmp->path_val = first->path_val;
	first->path = second->path;
	first->path_val = second->path_val;
	second->path = tmp->path;
	second->path_val = tmp->path_val;
}

void		sort_path(t_path *list)
{
	t_path	*tmp[2];
	t_path	*swap;

	tmp[0] = list;
	swap = (t_path *)ft_memalloc(sizeof(t_path));
	while (tmp[0]->next)
	{
		tmp[1] = list;
		while (tmp[1]->next)
		{
			if (tmp[1]->path_val > tmp[1]->next->path_val)
				swap_values(swap, tmp[1], tmp[1]->next);
			tmp[1] = tmp[1]->next;
		}
		tmp[0] = tmp[0]->next;
	}
	free(swap);
}

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

t_path		*create_path(t_link *link)
{
	int			i;
	t_path		*tmp;
	t_link		*l_tmp;

	tmp = NULL;
	if (link)
	{
		tmp = (t_path *)ft_memalloc(sizeof(t_path));
		tmp->path_val = count_link_elem(link);
		tmp->path = (int *)ft_memalloc(sizeof(int) * (tmp->path_val + 1));
		i = 0;
		l_tmp = link;
		while (l_tmp)
		{
			tmp->path[i] = l_tmp->pos;
			l_tmp = l_tmp->next;
			i++;
		}
		tmp->path[i] = -1;
		tmp->next = NULL;
	}
	return (tmp);
}

void		add_path(t_path **variants, t_path *path)
{
	t_path *tmp;

	tmp = NULL;
	if (!(*variants))
	{
		*variants = path;
	}
	else
	{
		tmp = *variants;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = path;
	}
}
