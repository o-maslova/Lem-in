#include "lem_in.h"

void		clear_vertex(t_vert *vertex)
{
	t_link		*tmp;

	tmp = NULL;
	ft_strdel(&(vertex->name));
	while (vertex->links)
	{
		// dprintf(g_fd, "name = %s\n", vertex->links->name);
		ft_strdel(&(vertex->links->name));
		// dprintf(g_fd, "name = %s\n", vertex->links->name);
		tmp = vertex->links;
		vertex->links = vertex->links->next;
		free(tmp);
	}
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

void		clear_link(t_link **link, int *i)
{
	t_link *tmp;

	*i = 0;
	tmp = NULL;
	while (*link)
	{
		tmp = *link;
		free(*link);
		*link = tmp->next;
	}
}