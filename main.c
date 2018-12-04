#include "lem_in.h"	

void		print_graph(t_coords *vertex)
{
	t_coords	*tmp;
	t_link		*tmp_links;

	tmp = vertex;
	while (tmp)
	{
		tmp_links = tmp->links;
		ft_printf("name = %s, pos = %d, (%d, %d), connect to:\n", tmp->name, tmp->pos, tmp->x, tmp->y);
		if (tmp->is_start == 1)
			ft_printf("IS START\n");
		if (tmp->is_end == 1)
			ft_printf("IS END\n");
		while (tmp_links)
		{
			ft_printf("%40s\n", tmp_links->name);
			tmp_links = tmp_links->next;
		}
		tmp = tmp->next;
	}
}

int			making_links(char *line, t_coords **list, t_coords	*tmp)
{
	char		**arr;

	tmp = *list;
	if (check_link(line) < 0)
		return (-1);
	arr = ft_strsplit(line, '-');
	// dprintf(g_fd, "w_amount = %d\n", w_amount);
	while (tmp)
	{
		g_amount = tmp->pos;
		if ((ft_strcmp(arr[0], tmp->name)) == 0)
			tmp->links = link_add(tmp->links, arr[1], tmp->pos);
		else if ((ft_strcmp(arr[1], tmp->name)) == 0)
			tmp->links = link_add(tmp->links, arr[0], tmp->pos);
		tmp = tmp->next;
	}
	ft_arrdel(arr);
	return (1);
}

int		list_fulling(int fd, t_coords **list, char **line, int pos)
{
	t_coords	*path;
	char		**arr;
	t_coords	*tmp;
	int			w_amount;

	path = NULL;
	if (pos == 1 || pos == 2)
		check_s_e(fd, line, list, pos);
	w_amount = ft_countchar(*line, ' ');
	if (w_amount != 2 && *line[0] == '#')
		return (0);
	if ((check_err(*line, list, w_amount, pos)) == -1)
		return (-1);
	arr = ft_strsplit(*line, ' ');
	if (!ft_isnumstr(arr[1]) || !ft_isnumstr(arr[2]))
		error_handling(3, arr, list);
	tmp = vertex_create(arr, pos);
	if (tmp->name[0] == 'L' || tmp->name[0] == '#')
		error_handling(4, arr, list);
	if (tmp->is_start == 1)
		path = vertex_create(arr, pos);
	add_vertex(list, tmp);
	ft_arrdel(arr);
	dprintf(g_fd, "tmp = %s\n", tmp->name);
	return (1);
}

void	parsing(int fd, t_coords **vertex)
{
	int			i;
	char		*line;
	t_coords	*v_tmp;

	i = 0;
	v_tmp = NULL;
	while (get_next_line(fd, &line) > 0)
	{
		if ((ft_strcmp(line, "##start")) == 0)
			i = list_fulling(fd, vertex, &line, 1);
		else if ((ft_strcmp(line, "##end")) == 0)
			i = list_fulling(fd, vertex, &line, 2);
		else if (!ft_strchr(line, '#') && ft_strchr(line, '-'))
			i = making_links(line, vertex, v_tmp);
		else
			i = list_fulling(fd, vertex, &line, 0);
		free(line);
		if (i < 0)
			break ;
	}
	g_amount = (g_amount + 1) / 2;
	dprintf(g_fd, "amount = %d\n", g_amount);
	print_graph(*vertex);
	clear_list(vertex);
}

int main(int argc, char **argv)
{
	int			fd;
	char		*line;
	t_coords	*vertex;

	if (argc != 2)
		exit(0);
	vertex = NULL;
	fd = open(argv[1], O_RDONLY);
	g_fd = open("log", O_RDWR | O_CREAT | O_TRUNC);
	g_amount = 0;
	// dprintf(g_fd, "%d\n", g_fd);
	get_next_line(fd, &line);
	if (!ft_isnumstr(line))
		error_handling(7, NULL, &vertex);
	g_ants = ft_atoi(line);
	free(line);
	parsing(fd, &vertex);
	system("leaks lem-in");
	return (0);
}