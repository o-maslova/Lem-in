#include "lem_in.h"

void	error_handling(int num, char **arr, t_coords **vert)
{
	dprintf(g_fd, "here\n");
	if (num == 1)
		perror("Error! Undefined start position!\n");
	if (num == 2)
		perror("Error! Undefined end position!\n");
	if (num == 3)
		perror("Error! Wrong coordinates format!\n");
	if (num == 4)
		perror("Error! Wrong data!\n");
	if (num == 5)
		perror("Error! Wrong link!\n");
	if (num == 6)
		perror("Error! Meet an empty line!\n");
	if (num == 7)
		perror("Error! Wrong number of ants!\n");
	ft_arrdel(arr);
	clear_list(vert);
	exit(0);
}