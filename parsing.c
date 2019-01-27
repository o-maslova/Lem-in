/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   parsing.c                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:56:52 by omaslova          #+#    #+#             */
/*   Updated: 2019/01/24 17:57:53 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		search_by_name(t_vert *graph, char *name)
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

int		making_links(char *line, t_vert **graph, int **links)
{
	char	**arr;
	int		vertex[2];

	if (check_link(line) < 0)
		return (-1);
	arr = ft_strsplit(line, '-');
	vertex[0] = search_by_name(*graph, arr[0]);
	vertex[1] = search_by_name(*graph, arr[1]);
	if (vertex[0] >= 0 && vertex[1] >= 0 && vertex[0] != vertex[1])
	{
		links[vertex[0]][vertex[1]] = 1;
		links[vertex[1]][vertex[0]] = 1;
	}
	ft_arrdel(arr);
	return (1);
}

void	add_node(t_graph **graph, char **arr, int pos)
{
	t_vert *tmp;

	tmp = vertex_create(*graph, arr, pos);
	if (tmp->name[0] == 'L' || tmp->name[0] == '#')
	{
		free(tmp);
		return ;
	}
	if (pos == 2)
		(*graph)->end_room = tmp->pos;
	add_vertex(&((*graph)->graph), tmp);
}

int		list_fulling(int fd, t_graph **graph, char **line, int pos)
{
	char	**arr;
	int		w_amount;

	arr = NULL;
	if (pos == 1 || pos == 2)
	{
		check_start_end(graph, pos, fd, line);
	}
	w_amount = ft_countchar(*line, ' ');
	if (w_amount != 2 || *(line[0]) == '#')
		return (0);
	if ((check_err(*line, graph, w_amount, pos)) == -1)
		return (-1);
	arr = ft_strsplit(*line, ' ');
	if (!ft_isnumstr(arr[1]) || !ft_isnumstr(arr[2]))
		error_handling(3, arr, graph);
	add_node(graph, arr, pos);
	ft_arrdel(arr);
	return (1);
}

int		parsing(int fd, t_graph **graph, char **line)
{
	int			i;
	static int	check;

	i = 0;
	if ((ft_strcmp(*line, "##start")) == 0)
		i = list_fulling(fd, graph, line, 1);
	else if ((ft_strcmp(*line, "##end")) == 0)
		i = list_fulling(fd, graph, line, 2);
	else if (!ft_strchr(*line, '#') && ft_strchr(*line, '-'))
	{
		if (check == 0)
			memory_allocate(graph, &check);
		i = making_links(*line, &((*graph)->graph), (*graph)->links);
	}
	else
		i = list_fulling(fd, graph, line, 0);
	return (i);
}
