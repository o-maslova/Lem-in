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

void		clear_list(t_vert **list)
{
	t_vert	*v_tmp;

	while (*list)
	{
		// dprintf(g_fd, "name = %s\n", (*list)->name);
		ft_strdel(&((*list)->name));
		v_tmp = *list;
		*list = (*list)->next;
		clear_vertex(v_tmp);
	}
	free(*list);
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