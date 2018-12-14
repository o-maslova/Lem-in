#include "lem_in.h"	

void		print_matrix(int **links)
{
	int i;
	int j;

	i = 0;
	dprintf(g_fd, " ");
	while (i < g_amount)
	{
		dprintf(g_fd, "%5d", i++);
	}
	dprintf(g_fd, "\n");
	i = 0;
	while (i < g_amount)
	{
		j = 0;
		while (j < g_amount)
		{
			if (j == 0)
				dprintf(g_fd, "%d", i);
			dprintf(g_fd, "%5d", links[i][j]);
			j++;
		}
		dprintf(g_fd, "\n");
		i++;
	}
}

void		print_graph(t_vert *graph)
{
	t_vert		*tmp;

	tmp = graph;
	while (tmp)
	{
		ft_printf("\nname = %s, pos = %d, (%d, %d)\n", tmp->name, tmp->pos, tmp->x, tmp->y);
		if (tmp->is_start == 1)
			ft_printf("IS START\n");
		if (tmp->is_end == 1)
			ft_printf("IS END\n");
		tmp = tmp->next;
	}
}

int			making_links(char *line, t_vert **graph, int **links)
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
	t_vert		*tmp;
	 
	tmp = vertex_create(arr, pos);
	if (tmp->name[0] == 'L' || tmp->name[0] == '#')
		error_handling(4, arr, graph);
	add_vertex(graph, tmp);
	if (pos == 1)
		g_start = tmp->pos;
}

int		list_fulling(int fd, t_vert **graph, char **line, int pos)
{
	char		**arr;
	int			w_amount;

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

int		**memory_allocate(int *check)
{
	int i;
	int **tmp;

	i = 0;
	*check += 1;
	g_amount += 1;
	tmp = (int **)ft_memalloc(sizeof(int *) * g_amount);
	while (i < g_amount)
	{
		tmp[i] = (int *)ft_memalloc(sizeof(int) * g_amount);
		i++;
	}
	return (tmp);
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
	// g_amount = (g_amount + 1) / 2;
	// dprintf(g_fd, "amount = %d\n", g_amount);
	print_graph(*graph);
	dprintf(g_fd, "\nstart = %d\n", g_start);
	print_matrix(links);
	new_algo(graph, links);
	clear_graph(graph);
	clear_matrix(links);
}

int main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_vert		*graph;

	if (argc != 2)
		exit(0);
	graph = NULL;
	fd = open(argv[1], O_RDONLY);
	g_fd = open("log", O_RDWR | O_CREAT | O_TRUNC);
	// g_amount = 0;
	// dprintf(g_fd, "%d\n", g_fd);
	get_next_line(fd, &line);
	if (!ft_isnumstr(line))
		error_handling(7, NULL, &graph);
	g_ants = ft_atoi(line);

	free(line);
	parsing(fd, &graph);
	system("leaks lem-in");
	return (0);
}