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

void		remove_part(t_link **path, int pos)
{
	t_link *fr;
	t_link *tmp;
	t_link *tmp_2;

	tmp = *path;
	while (tmp && tmp->pos != pos)
	{
		tmp = tmp->next;
		tmp_2 = tmp;
	}
	tmp = tmp->next;
	while (tmp)
	{
		fr = tmp->next;
		free(tmp);
		tmp = fr;
	}
	// tmp = NULL;
	if (tmp_2)
		tmp_2->next = NULL;
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
	static int	pos;
	int			check;
	int			k;

	k = 0;
	check = 0;
	// dprintf(g_fd,"i = %d, check = %d\n", i, check);
	while (++k < g_amount)
	{
		if (links[i][g_end] == 1)
		{
			add_link(path, g_end);
			match_visited(links, i, 2);
			break ;
		}
		if (links[i][k] == 1)
		{
			add_link(path, k);
			match_visited(links, k, 1);
			check = count_match(links[k]);
			if (check > 1)
				pos = k;
			if (check == 0)
			{
				remove_part(path, pos);
				return (pos);
			}
			i = k;
			k = 0;
		}
	}
	dprintf(g_fd,"\n");
	// print_matrix(links);
	return (0);
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
		while ((i = count_match(links[j])))
		{
			// if (links[i][j] == 1)
			// {
				// add_link(&path, j);
				// match_visited(links, j, 1);
				k = going_deeper(links, &path, j);
				if (k == 0)
				{
					variant = create_path(path);
					// print_path(path);
					add_path(&list, variant);
					clear_link(&path);
					j = 0;
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
