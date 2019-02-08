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

int		search_by_name(t_vert *graph, char *name, int amount)
{
	int		res;
	t_vert	*tmp;

	tmp = graph;
	while (tmp)
	{
		if (amount > 0)
			res = ft_strncmp(tmp->name, name, amount);
		else
			res = ft_strcmp(tmp->name, name);
		if (res == 0)
			return (tmp->pos);
		tmp = tmp->next;
	}
	return (-1);
}

int		making_links(char *line, t_graph **graph, int **links)
{
	char	*ptr;
	int		vertex[2];
	int		res;
	int		i;

	res = 1;
	ptr = ft_strchr(line, '-');
	i = ft_strlen(line) - ft_strlen(ptr);
	vertex[0] = search_by_name((*graph)->graph, line, i);
	vertex[1] = search_by_name((*graph)->graph, ptr + 1, 0);
	if (vertex[0] >= 0 && vertex[1] >= 0 && vertex[0] != vertex[1])
	{
		links[vertex[0]][vertex[1]] = 1;
		links[vertex[1]][vertex[0]] = 1;
	}
	else
		res = -1;
	return (res);
}

int		list_fulling(t_graph **graph, char **line, int pos)
{
	char	**arr;
	int		w_amount;

	arr = NULL;
	if (pos == 1 || pos == 2)
	{
		check_start_end(graph, pos, line);
	}
	w_amount = ft_countchar(*line, ' ');
	if (w_amount != 2 && *(line[0]) == '#')
		return (0);
	else if (w_amount != 2 && *(line[0]) != '#')
		return (-1);
	if ((check_err(*line, graph, w_amount, pos)) == -1)
		return (-1);
	arr = ft_strsplit(*line, ' ');
	if (!ft_isnumstr(arr[1]) || !ft_isnumstr(arr[2]))
		error_handling(3, arr, graph);
	add_node(graph, arr, pos);
	ft_arrdel(arr);
	return (1);
}

int		parsing(t_graph **graph, char **line)
{
	int			i;
	int			w_amount;
	static int	check;

	i = 0;
	w_amount = ft_countchar(*line, ' ');
	if ((ft_strcmp(*line, "##start")) == 0)
		i = list_fulling(graph, line, 1);
	else if ((ft_strcmp(*line, "##end")) == 0)
		i = list_fulling(graph, line, 2);
	else if (!ft_strchr(*line, '#') && ft_strchr(*line, '-') && w_amount == 0)
	{
		if (check == 0)
			memory_allocate(graph, &check);
		i = making_links(*line, graph, (*graph)->links);
	}
	else if (check == 0)
		i = list_fulling(graph, line, 0);
	else if (*line[0] != '#')
		i = -1;
	return (i);
}

void	pars_data(t_graph **graph)
{
	int			i;
	char		*line;

	i = 0;
	get_next_line(0, &line);
	if (!line)
		return ;
	while (*line == '#')
	{
		free(line);
		get_next_line(0, &line);
	}
	(*graph)->ant_amount = ft_atoi(line);
	if ((i = ft_isnumstr(line)) <= 0 || (*graph)->ant_amount == 0)
		error_handling(i, NULL, graph);
	ft_printf("%d\n", (*graph)->ant_amount);
	free(line);
	while (get_next_line(0, &line) > 0)
	{
		i = parsing(graph, &line);
		ft_printf("%s\n", line);
		free(line);
		if (i < 0)
			break ;
	}
}
