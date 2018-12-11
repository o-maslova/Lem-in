#include "lem_in.h"

void		clear_vertex(t_vert *vertex)
{
	t_link		*tmp;

	tmp = NULL;
	ft_strdel(&(vertex->name));
	free(vertex);
}

void		clear_graph(t_vert **graph)
{
	t_vert	*v_tmp;

	while (*graph)
	{
		// dprintf(g_fd, "name = %s\n", (*graph)->name);
		ft_strdel(&((*graph)->name));
		v_tmp = *graph;
		*graph = (*graph)->next;
		clear_vertex(v_tmp);
	}
	free(*graph);
}

void		clear_visits(t_vert **graph)
{
	t_vert	*v_tmp;

	v_tmp = *graph;
	while (v_tmp)
	{
		v_tmp->if_visit = 0;
		v_tmp = v_tmp->next;
	}
}

void		clear_matrix(int **links)
{
	int i;

	i = 0;
	while (i < g_amount)
	{
		free(links[i]);
		i++;
	}
	free(links);
}

void		clear_link(t_link **link)
{
	t_link *tmp;

	tmp = NULL;
	while (*link)
	{
		tmp = *link;
		free(*link);
		*link = tmp->next;
	}
}