/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   ant_output.c                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:58:08 by omaslova          #+#    #+#             */
/*   Updated: 2019/01/24 17:58:12 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	if_out(t_graph *graph, t_path *tmp, int *done_with, int ant)
{
	tmp->path[tmp->j] = -tmp->path[tmp->j];
	if (tmp->path[tmp->j] == graph->end_room)
		*done_with += 1;
	if (graph->c_flag == 1)
	{
		write(1, RED, 7);
		write(1, "L", 1);
		write(1, NC, 4);
		ft_printf("%d-", ant);
		write(1, tmp->path_color, 7);
	}
	else
	{
		write(1, NC, 4);
		ft_printf("L%d-", ant);
	}
	ft_printf("%s ", graph->arr[tmp->path[tmp->j]]);
	write(1, NC, 4);
}

int		out_it(t_graph *graph, int ant, int lim)
{
	int		done_with;
	int		that_ant;
	t_path	*tmp;

	done_with = 0;
	that_ant = lim + 1;
	ft_printf("\n");
	graph->str++;
	while (that_ant <= ant && graph->ant_in_string > 0)
	{
		tmp = graph->pathes;
		while (tmp && lim-- > 0)
			tmp = tmp->next;
		while (tmp && that_ant <= ant)
		{
			if (tmp && tmp->path[tmp->j] < 0)
			{
				if_out(graph, tmp, &done_with, that_ant++);
				graph->ant_in_string--;
			}
			tmp->j = tmp->j > 0 ? tmp->j - 1 : tmp->j;
			tmp = tmp->next;
		}
	}
	return (done_with);
}

void	match_rooms(t_path *path, int i, int ant, int *ant_in_string)
{
	int		j;
	t_path	*tmp;

	tmp = path;
	if (ant <= path->ant)
		j = 0;
	else
		j = (path->k)++;
	while (j < path->p_val && j < i)
	{
		path->path[j] = -path->path[j];
		*ant_in_string += 1;
		j++;
	}
}

void	ant_output(t_graph *graph)
{
	int		ant;
	int		done_with;
	t_path	*tmp;

	ant = 0;
	done_with = 0;
	while (done_with < graph->ant_amount)
	{
		tmp = graph->pathes;
		while (tmp)
		{
			if (tmp->i > 0 && graph->ant_amount > graph->p_num)
				match_rooms(tmp, tmp->i, ant, &graph->ant_in_string);
			if (tmp->i < tmp->p_val)
			{
				tmp->path[tmp->i] = -tmp->path[tmp->i];
				graph->ant_in_string++;
			}
			ant = ant < graph->ant_amount ? ant + 1 : ant;
			tmp->j = tmp->i;
			tmp->i = tmp->i < tmp->p_val - 1 ? tmp->i + 1 : tmp->i;
			tmp = tmp->next;
		}
		done_with += out_it(graph, ant, done_with);
	}
}
