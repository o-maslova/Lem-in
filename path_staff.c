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
	tmp->p_val = first->p_val;
	first->path = second->path;
	first->p_val = second->p_val;
	second->path = tmp->path;
	second->p_val = tmp->p_val;
}

void		sort_path(t_path *list)
{
	t_path	*tmp_1;
	t_path	*tmp_2;
	t_path	*swap;

	if (list)
	{
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
}

t_path		*create_path(t_graph *graph, t_algo *algo, int *used)
{
	int			i;
	int			j;
	t_path		*tmp;

	tmp = (t_path *)ft_memalloc(sizeof(t_path));
	tmp->p_val = algo->distances[END];
	tmp->path = (int *)ft_memalloc(sizeof(int) * tmp->p_val);
	i = tmp->p_val - 1;
	j = END;
	while (algo->prev[j])
	{
		tmp->path[--i] = algo->prev[j];
		used[tmp->path[i]] = 1;
		j = algo->prev[j];
	}
	tmp->path[tmp->p_val - 1] = END;
	tmp->next = NULL;
	return (tmp);
}

int			add_path(t_path **variants, t_path *path)
{
	t_path		*tmp;

	tmp = NULL;
	if (!(*variants))
		*variants = path;
	else
	{
		tmp = *variants;
		while (tmp->next)
			tmp = tmp->next;
		tmp->next = path;
	}
	return (1);
}
