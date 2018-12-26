#include "lem_in.h"

int		making_links(char *line, t_vert **graph, int **links)
{
	char	**arr;
	int		vertex[2];

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

void	add_node(t_graph **graph, char **arr, int pos)
{
	t_vert *tmp;

	tmp = vertex_create(*graph, arr, pos);
	if (tmp->name[0] == 'L' || tmp->name[0] == '#')
		error_handling(4, arr, graph);
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
		check_s_e(graph, pos);
		while (*line[0] == '#')
		{
			free(*line);
			get_next_line(fd, line);
		}
	}
	w_amount = ft_countchar(*line, ' ');
	if (w_amount != 2 && *(line[0]) == '#')
		return (0);
	if ((check_err(*line, graph, w_amount, pos)) == -1)
		return (-1);
	arr = ft_strsplit(*line, ' ');
	if (!ft_isnumstr(arr[1]) || !ft_isnumstr(arr[2]))
		error_handling(3, arr,graph);
	add_node(graph, arr, pos);
	ft_arrdel(arr);
	return (1);
}

void	parsing(int fd, t_graph **graph)
{
	int			i;
	char		*line;
	static int	check;

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
				memory_allocate(graph, &check);
			i = making_links(line, &((*graph)->graph), (*graph)->links);
		}
		else
			i = list_fulling(fd, graph, &line, 0);
		free(line);
		if (i < 0)
			break ;
	}
	// return (links);
}