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

void	clearing_function(t_graph *graph)
{
	clear_matrix(graph->links, graph->rooms);
	clear_path(&(graph->pathes));
	clear_graph(&(graph->graph));
	free(graph);
}

void	pars_data(int fd, t_graph **graph)
{
	int			i;
	char		*line;

	i = 0;
	get_next_line(fd, &line);
	while (*line == '#')
	{
		free(line);
		get_next_line(fd, &line);
	}
	if ((i = ft_isnumstr(line)) <= 0)
		error_handling(i, NULL, graph);
	(*graph)->ant_amount = ft_atoi(line);
	ft_printf("%d\n", (*graph)->ant_amount);
	free(line);
	while (get_next_line(fd, &line) > 0)
	{
		if ((i = parsing(fd, graph, &line)) > 0)
			ft_printf("%s\n", line);
		free(line);
		if (i < 0)
			break ;
	}
}

int		main(int argc, char **argv)
{
	int			fd;
	t_graph		*graph;

	graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	graph->graph = NULL;
	graph->links = NULL;
	fd = open(argv[1], O_RDONLY);
	if (argc != 2 || fd < 0)
		error_handling(7, NULL, &graph);
	pars_data(fd, &graph);
	algorithm(graph);
	clearing_function(graph);
	system("leaks lem-in");
	return (0);
}
