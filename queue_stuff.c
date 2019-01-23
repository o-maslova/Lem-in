#include "lem_in.h"

// void	initial(t_queue *queue)
// {
// 	queue->start = NULL;
// 	queue->end = NULL;
// }

void	put_to_queue(t_queue *queue, int pos)
{
	t_link *tmp;

	tmp = (t_link *)ft_memalloc(sizeof(t_link));
	tmp->pos = pos;
	tmp->next = NULL;
	if (queue->start == NULL)
		queue->start = tmp;
	else
		queue->end->next = tmp;
	queue->end = tmp;
	// if (queue->end != NULL)
	// 	queue->end->next = tmp;
	// else
	// 	queue->start = tmp;
}

int		pop_from_queue(t_queue *queue)
{
	int		pos;
	t_link	*tmp;
	// t_room	*room;

	tmp = queue->start;
	if (queue->start == queue->end)
		queue->end = NULL;
	queue->start = tmp->next;
	pos = tmp->pos;
	free(tmp);
	return (pos);
}