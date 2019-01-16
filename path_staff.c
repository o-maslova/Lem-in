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
	// // tmp->ant_in_path = first->ant_in_path;
	tmp->p_val = first->p_val;
	first->path = second->path;
	first->p_val = second->p_val;
	// // first->ant_in_path = second->ant_in_path;
	second->path = tmp->path;
	second->p_val = tmp->p_val;
	// // second->ant_in_path = tmp->ant_in_path;
}

void		sort_path(t_path *list)
{
	t_path	*tmp_1;
	t_path	*tmp_2;
	t_path	*swap;

	tmp_1 = list;
	swap = (t_path *)ft_memalloc(sizeof(t_path));
	while (tmp_1->next)
	{
		tmp_2 = list;
		while (tmp_2->next)
		{
			if (tmp_2->p_val > tmp_2->next->p_val)
				swap_values(swap, tmp_2, tmp_2->next);
			tmp_2 = tmp_2->next;
		}
		tmp_1 = tmp_1->next;
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
		tmp->p_val = count_link_elem(link);
		tmp->path = (int *)ft_memalloc(sizeof(int) * tmp->p_val);
		i = 0;
		l_tmp = link;
		while (l_tmp)
		{
			// tmp->path[i] = (int *)ft_memalloc(sizeof(int));
			tmp->path[i]= l_tmp->pos;
			// tmp->path[i][1] = 0;
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
