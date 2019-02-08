/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/01/24 17:58:18 by omaslova          #+#    #+#             */
/*   Updated: 2019/01/24 17:58:21 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	make_name_arr(t_graph *graph)
{
	t_vert	*tmp;

	tmp = graph->graph;
	graph->arr = (char **)ft_memalloc(sizeof(char *) * (graph->rooms + 1));
	while (tmp)
	{
		graph->arr[tmp->pos] = ft_strdup(tmp->name);
		tmp = tmp->next;
	}
	graph->arr[graph->rooms] = 0;
}

void	define_ant_and_path(t_graph *graph)
{
	int		i;
	int		ant;
	int		var;
	t_path	*tmp;

	i = 1;
	ant = graph->ant_amount;
	graph->pathes->ant = ant;
	tmp = graph->pathes;
	while (ant > 1 && tmp)
	{
		if (tmp->next)
		{
			var = (tmp->next->p_val - tmp->p_val) * i++;
			ant = ant - var > 0 ? ant - var : 0;
			if (ant == 0)
				break ;
			tmp->next->ant = ant;
		}
		tmp = tmp->next;
	}
	i = ant == 0 ? i - 1 : i;
	if (i != graph->p_num)
		clear_path(&(tmp->next));
	graph->p_num = i;
}

void	start_to_end(t_graph *graph, t_algo *algo, int *used)
{
	t_path	*variant;

	graph->links[0][END] = 0;
	algo->index = 1;
	algo->distances[END] = 1;
	algo->prev[END] = 0;
	algo->visited[END] = 1;
	variant = create_path(graph, algo, used);
	graph->p_num += add_path(graph, &(graph->pathes), variant);
	algo->visited[END] = 0;
	algo->distances[END] = 0;
}

void	print_variants(t_graph *graph)
{
	int		i;
	int		j;
	t_path	*tmp;

	tmp = graph->pathes;
	ft_putstr("\n---------------------------------------\n");
	ft_printf("%12POSSIBLE PATHES\n");
	ft_putstr("---------------------------------------\n");
	j = 0;
	while (tmp)
	{
		i = -1;
		write(1, WHITE, 7);
		ft_printf("%d: ", ++j);
		write(1, tmp->path_color, 7);
		while (++i < tmp->p_val - 1)
			ft_printf("%s, ", graph->arr[tmp->path[i]]);
		ft_printf("%s\n", graph->arr[tmp->path[i]]);
		write(1, WHITE, 7);
		ft_putstr("Rooms in that path: ");
		ft_putnbr(tmp->p_val);
		write(1, "\n", 1);
		write(1, NC, 4);
		tmp = tmp->next;
	}
}

void	algorithm(t_graph *graph, t_algo **algo)
{
	t_path	*variant;
	int		*used;

	variant = NULL;
	check_graph(graph);
	used = (int *)ft_memalloc(sizeof(int) * ROOMS);
	initial(algo, ROOMS);
	if (graph->links[0][END] == 1)
		start_to_end(graph, *algo, used);
	while ((variant = deeper(*algo, graph, used)) != NULL)
		graph->p_num += add_path(graph, &(graph->pathes), variant);
	if (graph->pathes != NULL)
	{
		sort_path(graph->pathes);
		make_name_arr(graph);
		if (graph->c_flag)
			print_variants(graph);
		define_ant_and_path(graph);
		ant_output(graph);
		write(1, "\n", 1);
		clear_arr(graph->arr);
	}
	else
		perror("ERROR! Not enough data!\n");
	free(used);
}
