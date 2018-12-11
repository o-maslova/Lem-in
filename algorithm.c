#include "lem_in.h"

void		print_path(t_link *path)
{
	int i;
	t_link *tmp;
	
	i = 0;
	tmp = path;
	while (tmp)
	{
		// dprintf(g_fd, "\nPATH #%d\n", i + 1);
		dprintf(g_fd, "%d\n", tmp->pos);
		tmp = tmp->next;
	}
}

int			check_path(t_link *path)
{
	int		check;
	t_link	*tmp;

	check = 0;
	tmp = path;
	while (tmp)
	{
		if (tmp->pos == g_amount)
			check = 1;
		tmp = tmp->next;
	}
	return (check);
}

void		going_deeper(int **links, t_link **path, int i, int j)
{
	
	j += 1;
	while (j < g_amount)
	{
		if (links[i][j] == 1)
		{
			add_link(path, j + 1);
			return(going_deeper(links, path, j, i));
		}
		j++;
	}
	// if (!check_path(*path))
	// 	clear_link(path);
	// else
	add_link(path, -1);
}

void		new_algo(t_vert **graph, int **links)
{
	// t_path	*variants;
	t_link	*path;
	int		i;
	int		j;

	i = 0;
	graph = NULL;
	path = NULL;
	while (i < g_amount)
	{
		j = 0;
		while (j < g_amount)
		{
			going_deeper(links, &path, i, j);
			print_path(path);
			j++;
			dprintf(g_fd,"\n");
		}
		break ;
	}
	// vert = *graph;
	// vert = search_vertex(*graph, START);
	// 
}