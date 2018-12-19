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

void		copy_path(t_path **dst, t_link *src)
{
	t_link	*l_tmp;
	int		i;

	i = 0;
	l_tmp = src;
	if (l_tmp)
	{
		while (l_tmp)
		{
			(*dst)->path[i] = l_tmp->pos;
			l_tmp = l_tmp->next;
			i++;
		}
	}
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
		// copy_path(&tmp, link);
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
