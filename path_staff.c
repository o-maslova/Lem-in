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
	t_path	*tmp1;
	t_path	*tmp2;
	t_path	*swap;

	tmp1 = list;
	swap = (t_path *)ft_memalloc(sizeof(t_path));
	while (tmp1->next)
	{
		tmp2 = list;
		while (tmp2->next)
		{
			if (tmp2->path_val > tmp2->next->path_val)
			{
				swap_values(swap, tmp2, tmp2->next);
			}
			tmp2 = tmp2->next;
		}
		tmp1 = tmp1->next;
	}
	free(swap);
	// return (list);
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
	int		i;
	t_path	*tmp;
	t_link	*l_tmp;

	tmp = NULL;
	if (link)
	{
		tmp = (t_path *)ft_memalloc(sizeof(t_path));
		i = count_link_elem(link);
		tmp->path_val = i;
		tmp->path = (int *)ft_memalloc(sizeof(int) * i);
		i = 0;
		l_tmp = link;
		while (l_tmp)
		{
			tmp->path[i] = l_tmp->pos;
			l_tmp = l_tmp->next;
			i++;
		}
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
