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

void	clearing_fun(t_graph *graph)
{
	clear_matrix(graph->links, graph->rooms);
	clear_arr(graph->arr);
	clear_path(&(graph->pathes));
	clear_graph(&(graph->graph));
}

int		main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_graph		*graph;

	if (argc != 2)
		exit(0);
	graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	graph->graph = NULL;
	graph->links = NULL;
	fd = open(argv[1], O_RDONLY);
	g_fd = open("log", O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 0)
		exit(0);
	get_next_line(fd, &line);
	if (!ft_isnumstr(line))
		error_handling(7, NULL, &graph);
	graph->ant_amount = ft_atoi(line);
	free(line);
	parsing(fd, &graph);
	// print_matrix(g_fd, *graph);
	print_graph(graph);
	algorithm(graph);
	clearing_fun(graph);
	free(graph);
	system("leaks lem-in");
	return (0);
}
