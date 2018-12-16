/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   search.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:07:27 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:07:28 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			search_by_name(t_vert *graph, char *name)
{
	int		res;
	t_vert	*tmp;

	tmp = graph;
	while (tmp)
	{
		res = ft_strcmp(tmp->name, name);
		if (res == 0)
			return (tmp->pos);
		tmp = tmp->next;
	}
	return (-1);
}
