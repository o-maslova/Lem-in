#include "lem_in.h"

void	initial(t_algo **algo, int num)
{
	*algo = (t_algo *)ft_memalloc(sizeof(t_algo));
	(*algo)->distances = (int *)ft_memalloc(sizeof(int) * num);
	(*algo)->visited = (int *)ft_memalloc(sizeof(int) * num);
	(*algo)->prev = (int *)ft_memalloc(sizeof(int) * num);
	(*algo)->queue = (int *)ft_memalloc(sizeof(int) * (num * 2));
	ft_memset((*algo)->queue, -1, (sizeof(int) * (num + 1)));
	(*algo)->index = 1;
}

void	clear(t_algo *algo, int num)
{
	int i;

	i = 0;
	algo->index = 1;
	while (i < num)
	{
		algo->visited[i] = 0;
		algo->distances[i] = 0;
		algo->prev[i] = 0;
		algo->queue[i] = -1;
		i++;
	}
}

int		find_end(t_algo *algo, t_graph *graph, int i, int *used)
{
	int k;

	k = 1;
	while (k < ROOMS)
	{
		if (graph->links[i][k] == 1 && algo->visited[k] != 1 && used[k] != 1)
		{
			algo->queue[algo->index] = k;
			algo->index++;
			algo->distances[k] = algo->distances[i] + 1;
			algo->prev[k] = i;
			algo->visited[k] = 1;
			if (k == END)
				return (1);
		}
		k++;
	}
	return (0);
}

int		pop_first_elem(t_algo *algo)
{
	int i;
	int ret;

	i = 0;
	ret = algo->queue[0];
	while (algo->queue[i] != -1)
	{
		algo->queue[i] = algo->queue[i + 1];
		i++;
	}
	return (ret);
}

t_path	*deeper(t_algo *algo, t_graph *graph, int *used)
{
	t_path	*variant;
	int		indx;
	int		vert;

	indx = 0;
	algo->queue[indx] = graph->graph->pos;
	while (algo->queue[indx] != -1)
	{
		vert = pop_first_elem(algo);
		algo->index--;
		if (find_end(algo, graph, vert, used))
		{
			variant = create_path(graph, algo, used);
			clear(algo, ROOMS);
			return (variant);
		}
	}
	clear(algo, ROOMS);
	return (NULL);
}