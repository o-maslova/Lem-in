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

void	clear_algo(t_algo **algo)
{
	free((*algo)->distances);
	free((*algo)->prev);
	free((*algo)->visited);
	free((*algo)->queue);
	free(*algo);
}

void	clearing_function(t_graph *graph)
{
	clear_matrix(graph->links, graph->rooms);
	clear_path(&(graph->pathes));
	ft_arrdel(graph->colors);
	clear_graph(&(graph->graph));
	free(graph);
}

void	colors(t_graph *graph)
{
	int		i;

	i = 0;
	graph->colors = (char **)ft_memalloc(sizeof(char *) * 6);
	while (i < 5)
		graph->colors[i++] = (char *)ft_memalloc(sizeof(char) * 8);
	graph->colors[0] = ft_strcpy(graph->colors[0], "\e[91m");
	graph->colors[1] = ft_strcpy(graph->colors[1], "\e[92m");
	graph->colors[2] = ft_strcpy(graph->colors[2], "\e[93m");
	graph->colors[3] = ft_strcpy(graph->colors[3], "\e[94m");
	graph->colors[4] = ft_strcpy(graph->colors[4], "\e[95m");
	graph->colors[5] = 0;
}

void	total_out(int strings)
{
	write(1, RED, 7);
	ft_putstr("\nALL YOUR ANTS ARE IN ANTHILL FOR ");
	ft_putnbr(strings);
	ft_putstr(" LINES\n");
}

int		main(int argc, char **argv)
{
	t_algo		*algo;
	t_graph		*graph;

	graph = (t_graph *)ft_memalloc(sizeof(t_graph));
	algo = NULL;
	graph->graph = NULL;
	graph->links = NULL;
	pars_data(&graph);
	if (argc == 2 && (ft_strcmp(argv[1], "-c") == 0))
		graph->c_flag = 1;
	colors(graph);
	algorithm(graph, &algo);
	if (graph->str > 0 && graph->c_flag)
		total_out(graph->str);
	clear_algo(&algo);
	clearing_function(graph);
	return (0);
}
