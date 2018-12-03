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

void		clear_vertex(t_coords **vertex)
{
	t_link		*tmp;
	t_coords	*v_tmp;

	while (*vertex)
	{
		// dprintf(g_fd, "name = %s\n", (*vertex)->name);
		ft_strdel(&((*vertex)->name));
		while ((*vertex)->links)
		{
			// dprintf(g_fd, "name = %s\n", (*vertex)->links->name);
			ft_strdel(&((*vertex)->links->name));
			// dprintf(g_fd, "name = %s\n", (*vertex)->links->name);
			tmp = (*vertex)->links;
			(*vertex)->links = (*vertex)->links->next;
			free(tmp);
		}
		v_tmp = *vertex;
		*vertex = (*vertex)->next;
		free(v_tmp);
	}
	free(*vertex);
}

void		making_links(char *line, t_coords **list)
{
	t_coords	*tmp;
	char		**arr;
	int			res;

	tmp = *list;
	arr = ft_strsplit(line, '-');
	while (tmp)
	{
		if ((res = ft_strcmp(arr[0], tmp->name)) == 0)
		{
			tmp->links = link_add(tmp->links, arr[1]);
		}
		tmp = tmp->next;
	}
	ft_arrdel(arr, 2);
}

void		list_fulling(int fd, t_coords **list, char **line, int pos)
{
	char		**arr;
	t_coords	*tmp;

	if (pos == 1 || pos == 2)
	{
		free(*line);
		get_next_line(fd, line);
	}
	arr = ft_strsplit(*line, ' ');
	tmp = vertex_create(arr, pos);
	add_vertex(list, tmp);
	ft_arrdel(arr, 3);
}

void	parsing(int fd, t_coords **vertex)
{
	char		*line;

	while (get_next_line(fd, &line) > 0)
	{
		if (ft_strstr(line, "##start"))
			list_fulling(fd, vertex, &line, 1);
		else if (ft_strstr(line, "##end"))
			list_fulling(fd, vertex, &line, 2);
		else if (!ft_strchr(line, '#') && ft_strchr(line, ' '))
			list_fulling(fd, vertex, &line, 0);
		else if (!ft_strchr(line, ' ') && ft_strchr(line, '-'))
			making_links(line, vertex);
		free(line);
	}
	print_graph(*vertex);
	clear_vertex(vertex);
}

int main(int argc, char **argv)
{
	int			fd;
	t_coords	*vertex;

	if (argc != 2)
		exit(0);
	vertex = NULL;
	fd = open(argv[1], O_RDONLY);
	g_fd = open("log", O_RDWR | O_CREAT | O_TRUNC);
	parsing(fd, &vertex);
	system("leaks lem-in");
	return (0);
}