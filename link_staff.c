/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   link_staff.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:07:06 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:07:08 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

t_link		*create_link(int pos)
{
	t_link *node;

	node = (t_link *)ft_memalloc(sizeof(t_link));
	node->pos = pos;
	node->next = NULL;
	return (node);
}

void		add_link(t_link **path, int pos)
{
	t_link *tmp;

	tmp = NULL;
	if (!(*path))
		*path = create_link(pos);
	else
	{
		tmp = *path;
		if (tmp->next)
			while (tmp->next)
				tmp = tmp->next;
		tmp->next = create_link(pos);
	}
}

int			count_link_elem(t_link *list)
{
	int		res;
	t_link	*tmp;

	res = 0;
	if (list)
	{
		tmp = list;
		while (tmp)
		{
			res++;
			tmp = tmp->next;
		}
	}
	return (res);
}
