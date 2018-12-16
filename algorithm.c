/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algorithm.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:04:49 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:05:48 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

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
	if (tmp)
	{
		tmp = tmp->next;
		while (tmp)
		{
			fr = tmp->next;
			free(tmp);
			tmp = fr;
		}
	}
	if (tmp_2 && tmp_2->next)
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

void		going_deeper(t_path	**list, int **links, t_link **path, int i)
{
	t_path		*variant;
	static int	pos;
	int			check;
	int			k;

	k = 0;
	check = 0;
	while (++k < g_amount)
	{
		if (links[i][g_end] == 1)
		{
			add_link(path, g_end);
			// match_visited(links, i, 1);
			match_visited(links, i, 2);
			variant = create_path(*path);
			dprintf(g_fd,"NEW_PATH\n");
			print_path(*path);
			add_path(list, variant);
			remove_part(path, pos);
			break ;
		}
		if (links[i][k] == 1)
		{
			add_link(path, k);
			match_visited(links, k, 1);
			// match_visited(links, i, 2);
			check = count_match(links[k]);
			if (check > 1)
			{
				// add_link(path, -1);
				pos = k;
				going_deeper(list, links, path, k);
			}
			if (check == 0)
			{
				remove_part(path, pos);
				continue ;
			}
			i = k;
			k = 0;
		}
	}
	dprintf(g_fd,"\n");
	// print_matrix(links);
}

void		algorithm(int **links)
{
	t_path	*list;
	t_link	*path;
	int		i;
	int		j;

	path = NULL;
	list = NULL;
	j = 0;
	i = count_match(links[j]);
	while (i > 0)
	{
		while (links[0][j] != 1)
			j++;
		add_link(&path, j);
		match_visited(links, j, 1);
		going_deeper(&list, links, &path, j);
		clear_link(&path);
		i--;
	}
	// print_variants(list);
	clear_path(&list);
}
