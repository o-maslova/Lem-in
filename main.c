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

int		main(int argc, char **argv)
{
	int			fd;
	int			**links;
	char		*line;
	t_vert		*graph;

	if (argc != 2)
		exit(0);
	graph = NULL;
	links = NULL;
	fd = open(argv[1], O_RDONLY);
	g_fd = open("log", O_RDWR | O_CREAT | O_TRUNC);
	if (fd < 0)
		exit(0);
	get_next_line(fd, &line);
	if (!ft_isnumstr(line))
		error_handling(7, NULL, &graph);
	g_ants = ft_atoi(line);
	free(line);
	links = parsing(fd, &graph, links);
	print_matrix(g_fd, links);
	algorithm(links);
	print_graph(graph);
	clear_graph(&graph);
	system("leaks lem-in");
	return (0);
}
