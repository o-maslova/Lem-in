#include "lem_in.h"

void		remove_last(t_link **path)
{
	t_link *tmp;

	if (!(*path))
		return ;
	tmp = *path;
	while (tmp->next->next)
	{
		tmp = tmp->next;
	}
	if (tmp->next)
		free(tmp->next);
	tmp->next = NULL;
}

void		remove_part(t_link **path, int pos)
{
	t_link *fr;
	t_link *tmp;
	t_link *tmp_2;

	tmp = *path;
	tmp_2 = NULL;
	if (tmp->pos == pos)
	{
		clear_link(&(*path)->next);
		return ;
	}
	while (tmp && tmp->pos != pos)
	{
		tmp_2 = tmp;
		tmp = tmp->next;
	}
	if (tmp)
	{
		while (tmp)
		{
			fr = tmp->next;
			free(tmp);
			tmp = fr;
		}
		tmp_2->next = NULL;
	}
}
