/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   errors.c                                           :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:06:37 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:06:42 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

void	error(int num)
{
	if (num == -1)
		perror("ERROR!\n");
	if (num == 0)
		perror("ERROR! Wrong number of ants!\n");
	if (num == 1)
		perror("ERROR! Undefined start position!\n");
	if (num == 2)
		perror("ERROR! Undefined end position!\n");
	if (num == 3)
		perror("ERROR! Wrong coordinates format!\n");
	if (num == 4)
		perror("ERROR! Wrong data!\n");
}

void	error_handling(int num, char **arr, t_graph **graph)
{
	if (num == -1 || num == 0 || num == 1 || num == 2 || num == 3 || num == 4)
		error(num);
	if (num == 5)
		perror("ERROR! Wrong link!\n");
	if (num == 6)
		perror("ERROR! Not enough data!\n");
	if (num == 7)
		ft_printf("usage: ./lem-in ant_farm_map.txt\n");
	if (num == 8)
		ft_printf("ERROR! Duplicate room name.\n");
	if (num == 9)
		ft_printf("ERROR! Duplicate room coordinates.\n");
	if (num == 10)
		ft_printf("ERROR! Link with not existing room.\n");
	if (num == 11)
		ft_printf("ERROR! Wrong room name!\n");
	ft_arrdel(arr);
	if (graph)
	{
		clear_graph(&((*graph)->graph));
		free(*graph);
	}
	system("leaks lem-in");
	exit(0);
}
