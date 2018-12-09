#include "lem_in.h"	

void		print_graph(t_vert *graph)
{
	t_vert		*tmp;
	t_link		*tmp_links;

	tmp = graph;
	while (tmp)
	{
		tmp_links = tmp->links;
		ft_printf("\nname = %s, pos = %d, (%d, %d), connect to:\n", tmp->name, tmp->pos, tmp->x, tmp->y);
		if (tmp->is_start == 1)
			ft_printf("IS START\n");
		if (tmp->is_end == 1)
			ft_printf("IS END\n");
		while (tmp_links)
		{
			ft_printf("%40s, %d\n", tmp_links->name, tmp_links->pos);
			tmp_links = tmp_links->next;
		}
		// dprintf(g_fd, "sizeof node = %lu\n", sizeof(t_vert));
		tmp = tmp->next;
	}
	// dprintf(g_fd, "sizeof list = %lu\n", sizeof(*graph));
}

int			making_links(char *line, t_vert **graph)
{
	t_vert	*tmp;
	char	**arr;

	tmp = *graph;
	if (check_link(line) < 0)
		return (-1);
	arr = ft_strsplit(line, '-');
	// dprintf(g_fd, "w_amount = %d\n", w_amount);
	while (tmp)
	{
		// g_amount = tmp->pos;
		if ((ft_strcmp(arr[0], tmp->name)) == 0)
			link_add_1(*graph, &(tmp->links), arr[1]);
		else if ((ft_strcmp(arr[1], tmp->name)) == 0)
			link_add_1(*graph, &(tmp->links), arr[0]);
		tmp = tmp->next;
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
	// dprintf(g_fd, "tmp = %s\n", tmp->name);
	return (1);
}

void	parsing(int fd, t_vert **graph)
{
	int			i;
	char		*line;
	t_link		*path;

	i = 0;
	path = (t_link *)ft_memalloc(sizeof(t_link));
	path->name = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if ((ft_strcmp(line, "##start")) == 0)
			i = list_fulling(fd, graph, &line, 1);
		else if ((ft_strcmp(line, "##end")) == 0)
			i = list_fulling(fd, graph, &line, 2);
		else if (!ft_strchr(line, '#') && ft_strchr(line, '-'))
			i = making_links(line, graph);
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
	algorithm(graph);
	clear_graph(graph);
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