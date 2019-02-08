/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:08:03 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:08:16 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	check_graph(t_graph *graph)
{
	int		check;
	t_vert	*tmp;

	check = 0;
	tmp = graph->graph;
	while (tmp)
	{
		if (tmp->is_start == 1 || tmp->is_end == 1)
			check++;
		tmp = tmp->next;
	}
	if (check < 2 || graph->links == NULL)
		error_handling(6, NULL, &graph);
	write(1, RED, 7);
	ft_printf("IF YOU WANT COLORFUL OUTPUT YOUR FLAG SHOULD BE -c\n");
	write(1, YELLOW, 7);
}

int		check_err(char *line, t_graph **graph, int n, int pos)
{
	if (n > 2 && *line != '#')
		return (-1);
	else if (ft_emptyline(line))
		return (-1);
	else if (*line != '#' && n != 2 && n != 0)
		error_handling(3, NULL, graph);
	else if ((pos == 1 || pos == 2) && n == 0)
		error_handling(pos, NULL, graph);
	return (1);
}

void	check_start_end(t_graph **graph, int n, char **line)
{
	static int	start;
	static int	end;

	start = n == 1 ? start + 1 : start;
	end = n == 2 ? end + 1 : end;
	if (start > 1)
		error_handling(1, NULL, graph);
	else if (end > 1)
		error_handling(2, NULL, graph);
	ft_printf("%s\n", *line);
	free(*line);
	get_next_line(0, line);
	while (*line[0] == '#')
	{
		free(*line);
		get_next_line(0, line);
	}
}
