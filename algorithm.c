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

void		swap(int *a, int *b)
{
	int tmp;

	tmp = *a;
	*a = *b;
	*b = tmp;
}

// void		going_deeper(int **links, t_link **path, int row, int col)
// {
// 	t_path	*list;
// 	t_path	*variant;
// 	int			i;
// 	int			j;
// 	int			tmp;

// 	i = row;
// 	list = NULL;
// 	while (i < g_amount)
// 	{
// 		j = 0;
// 		if (links[row][col] == -1)
// 			return ;
// 		while (++j < g_amount)
// 		{
// 			if (links[i][j] == 1)
// 			{
// 				add_link(path, j + 1);
// 				tmp = i;
// 				swap(&i, &j);
// 				continue ;
// 			}
// 			if (links[i][tmp] == -1)
// 				links[tmp][i] = -1;
// 		}
// 		print_path(*path);
// 		dprintf(g_fd, "i = %d, tmp = %d\n", i, tmp);
// 		if (i != g_amount - 1)
// 			links[i][tmp] = -1;
// 		// else if (links[i][tmp] == 1 && i != g_amount - 1)
// 		// 	links[i][tmp] = -1;
// 		else
// 			links[tmp][i] = -1;
// 		i = row;
// 		if (check_path(*path))
// 		{
// 			variant = create_path(*path);
// 			add_path(&list, variant);
// 		}
// 		dprintf(g_fd, "\n");
// 		print_matrix(links);
// 		clear_link(path);
// 	}
// }


void		going_deeper(int **links, t_link **path, int i, int j)
{
	t_path	*list;
	t_path	*variant;
	// int			tmp;

	list = NULL;
	while (++j < g_amount)
	{
		if (links[i][j] == 1)
		{
			add_link(path, j + 1);
			links[i][j] = -1;
			if (links[i][g_amount - 1] == 1)
			{
				links[i][g_amount - 1] = -1;
				break ;
			}
			return (going_deeper(links, path, j, i));
		}
		// j++;
	}
	print_path(*path);
	// dprintf(g_fd, "i = %d, tmp = %d\n", i, tmp);
	variant = create_path(*path);
	add_path(&list, variant);
	clear_link(path);
	print_matrix(links);
}

void		new_algo(t_vert **graph, int **links)
{
	t_path	*list;
	t_link	*path;
	int		i;
	int		j;

	graph = NULL;
	path = NULL;
	list = NULL;
	i = 0;
	while (i < g_amount)
	{
		j = 0;
		while (j < g_amount)
		{
			if (links[0][j] == 1)
			{
				add_link(&path, j + 1);
				links[0][j] = -1;
				// j -= 1;
				going_deeper(links, &path, j, i);
				// print_path(path);
				// if (check_path(path))
				// {
				// 	variant = create_path(path);
				// 	add_path(&list, variant);
				// }
				// clear_link(&path);
				// j = 1;
			// }
				// if (links[i][j] == 1)
				// {
					// i = 1;
				dprintf(g_fd,"\n");
				// break ;
			}
			j++;
		}
		break ;
	}
	// vert = *graph;
	// vert = search_vertex(*graph, START);
	// 
}