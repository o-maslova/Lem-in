/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   main.c                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:07:17 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:07:18 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int		making_links(char *line, t_vert **graph, int **links)
{
	t_vert	*tmp;
	char	**arr;
	int		vertex[2];

	tmp = *graph;
	if (check_link(line) < 0)
		return (-1);
	arr = ft_strsplit(line, '-');
	vertex[0] = search_by_name(*graph, arr[0]);
	vertex[1] = search_by_name(*graph, arr[1]);
	if (vertex[0] >= 0 && vertex[1] >= 0)
	{
		links[vertex[0]][vertex[1]] = 1;
		links[vertex[1]][vertex[0]] = 1;
	}
	ft_arrdel(arr);
	return (1);
}

void	add_node(t_vert **graph, char **arr, int pos)
{
	t_vert *tmp;

	tmp = vertex_create(arr, pos);
	if (tmp->name[0] == 'L' || tmp->name[0] == '#')
		error_handling(4, arr, graph);
	if (pos == 2)
		g_end = tmp->pos;
	add_vertex(graph, tmp);
}

int		list_fulling(int fd, t_vert **graph, char **line, int pos)
{
	char	**arr;
	int		w_amount;

	if (pos == 1 || pos == 2)
		check_s_e(fd, line, graph, pos);
	w_amount = ft_countchar(*line, ' ');
	if (w_amount != 2 && *line[0] == '#')
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

void	parsing(int fd, t_vert **graph)
{
	int			i;
	int			**links;
	static int	check;
	char		*line;

	i = 0;
	while (get_next_line(fd, &line) > 0)
	{
		if ((ft_strcmp(line, "##start")) == 0)
			i = list_fulling(fd, graph, &line, 1);
		else if ((ft_strcmp(line, "##end")) == 0)
			i = list_fulling(fd, graph, &line, 2);
		else if (!ft_strchr(line, '#') && ft_strchr(line, '-'))
		{
			if (check == 0)
				links = memory_allocate(&check);
			i = making_links(line, graph, links);
		}
		else
			i = list_fulling(fd, graph, &line, 0);
		free(line);
		if (i < 0)
			break ;
	}
	print_graph(*graph);
	// print_matrix(links);
	algorithm(links);
	clear_graph(graph);
	clear_matrix(links);
}

int		main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_vert		*graph;

	if (argc != 2)
		exit(0);
	graph = NULL;
	fd = open(argv[1], O_RDONLY);
	g_fd = open("log", O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 0)
		exit(0);
	get_next_line(fd, &line);
	if (!ft_isnumstr(line))
		error_handling(7, NULL, &graph);
	g_ants = ft_atoi(line);
	free(line);
	parsing(fd, &graph);
	system("leaks lem-in");
	return (0);
}
