#include "lem_in.h"

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