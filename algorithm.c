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

void		print_variants(t_path *path)
{
	int i;
	t_path *tmp;

	tmp = path;
	while (tmp)
	{
		i = -1;
		while (++i < tmp->path_val)
			dprintf(g_fd, "%d\n", tmp->path[i]);
		dprintf(g_fd, "\n");
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


void		match_visited(int **links, int i, int order)
{
	int k;

	k = 0;
	if (order == 1)
	{
		while (k < g_amount)
		{
			if (links[k][i] == 1)
				links[k][i] = -1;
			k++;
		}
	}
	else if (order == 2)
	{
		while (k < g_amount)
		{
			if (links[i][k] == 1)
				links[i][k] = -1;
			k++;
		}
	}
}

void		remove_last(t_link **path)
{
	t_link *tmp;
	t_link *fr;

	tmp = *path;
	while (tmp->next)
		tmp = tmp->next;
	fr = tmp;
	free(tmp);
	tmp = NULL;
	// fr = NULL;
}

int			count_match(int *links)
{
	int i;
	int count;

	i = 0;
	count = 0;
	while (i < g_amount)
	{
		if (links[i] == 1)
			count++;
		i++;
	}
	return (count);
}

int			going_deeper(int **links, t_link **path, int i)
{
	int	check;
	int			k;

	k = 0;
	check = 0;
	// if ((check = count_match(links[i])) == 0)
	// 	return (-1);
	// dprintf(g_fd,"i = %d, check = %d\n", i, check);
	while (++k < g_amount)
	{
		if (links[i][g_end] == 1)
		{
			add_link(path, g_end);
			match_visited(links, i, 2);
			// check = 1;
			break ;
		}
		if (links[i][k] == 1)
		{
			add_link(path, k);
			match_visited(links, k, 1);
			if ((check = count_match(links[k])) == 0)
				return (i);
			i = k;
			k = 0;
			// return (k);
		}
		// continue ;
	}
	dprintf(g_fd,"\n");
	print_matrix(links);
	print_path(*path);
	return (0);
	// if (check == 0)
}

void		new_algo(int **links)
{
	t_path	*list;
	t_path	*variant;
	t_link	*path;
	int		i;
	int		j;
	int		k;

	path = NULL;
	list = NULL;
	i = 0;
	while (i < g_amount)
	{
		j = 0;
		while ((i = count_match(links[0])))
		{
			// if (links[i][j] == 1)
			// {
				// add_link(&path, j);
				// match_visited(links, j, 1);
				k = going_deeper(links, &path, j);
				if (k == 0)
				{
					variant = create_path(path);
					add_path(&list, variant);
					clear_link(&path);
				}
				else
				{
					// j--;
					// remove_last(&path);
					j = k;
					// continue ;
				}
				dprintf(g_fd,"i = %d\n", i);
			// }
			// j++;
		}
		print_variants(list);
		break ;
	}
	clear_path(&list);
}
