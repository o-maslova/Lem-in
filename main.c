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
	// ft_printf("\n");
	// system("leaks lem-in");
	return (0);
}
