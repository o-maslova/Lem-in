#include "lem_in.h"	

void		print_graph(t_coords *vertex)
{
	t_coords	*tmp;
	t_link		*tmp_links;

	tmp = vertex;
	while (tmp)
	{
		tmp_links = tmp->links;
		ft_printf("name = %s, (%d, %d), connect to:\n", tmp->name, tmp->x, tmp->y);
		while (tmp_links)
		{
			ft_printf("%40s\n", tmp_links->name);
			tmp_links = tmp_links->next;
		}
		tmp = tmp->next;
	}
}

int			check_link(char *line)
{
	int			w_amount;

	w_amount = 0;
	w_amount = ft_countchar(line, '-');
	if (w_amount != 1)
		return (-1);
	if (ft_strchr(line, ' '))
		return (-1);
	return (0);
}

int			making_links(char *line, t_coords **list, t_coords	*tmp)
{
	char		**arr;
	int			st_counter;
	int			end_counter;

	tmp = *list;
	st_counter = 0;
	end_counter = 0;
	if (check_link(line) < 0)
		return (-1);
	arr = ft_strsplit(line, '-');
	// dprintf(g_fd, "w_amount = %d\n", w_amount);
	while (tmp)
	{
		st_counter = tmp->is_start == 1 ? st_counter + 1 : st_counter;
		end_counter = tmp->is_end == 1 ? end_counter + 1 : end_counter;
		if ((ft_strcmp(arr[0], tmp->name)) == 0)
			tmp->links = link_add(tmp->links, arr[1]);
		tmp = tmp->next;
	}
	if (st_counter > 1 || st_counter == 0)
		error_handling(1, arr, list);
	if (end_counter > 1 || end_counter == 0)
		error_handling(2, arr, list);
	ft_arrdel(arr);
	return (1);
}

void		list_fulling(int fd, t_coords **list, char **line, int pos)
{
	char		**arr;
	t_coords	*tmp;
	int			w_amount;

	w_amount = 0;
	if (pos == 1 || pos == 2)
	{
		free(*line);
		get_next_line(fd, line);
	}
	w_amount = ft_countchar(*line, ' ');
	if (w_amount > 2 && *line[0] == '#')
		return ;
	else if (*line[0] != '#' && w_amount != 2 && w_amount != 0)
		error_handling(4, NULL, list);
	else if ((pos == 1 || pos == 2) && w_amount == 0)
		error_handling(pos, NULL, list);
	arr = ft_strsplit(*line, ' ');
	if (!ft_isnumstr(arr[1]) || !ft_isnumstr(arr[2]))
		error_handling(3, arr, list);
	tmp = vertex_create(arr, pos);
	if (tmp->name[0] == 'L' || tmp->name[0] == '#')
		error_handling(4, arr, list);
	add_vertex(list, tmp);
	ft_arrdel(arr);
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
		if (ft_emptyline(line))
			error_handling(6, NULL, vertex);
		if ((ft_strcmp(line, "##start")) == 0)
			list_fulling(fd, vertex, &line, 1);
		else if ((ft_strcmp(line, "##end")) == 0)
			list_fulling(fd, vertex, &line, 2);
		else if (!ft_strchr(line, '#') && ft_strchr(line, '-'))
			i = making_links(line, vertex, v_tmp);
		else
			list_fulling(fd, vertex, &line, 0);
		free(line);
		if (i < 0)
			break ;
	}
	print_graph(*vertex);
	clear_vertex(vertex);
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
	get_next_line(fd, &line);
	if (ft_isnumstr(line))
		g_ants = ft_atoi(line);
	else
		error_handling(7, NULL, &vertex);
	free(line);
	// dprintf(g_fd, "ants = %d\n", g_ants);
	parsing(fd, &vertex);
	system("leaks lem-in");
	return (0);
}