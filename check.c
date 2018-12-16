/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   check.c                                            :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/12/16 18:08:03 by omaslova          #+#    #+#             */
/*   Updated: 2018/12/16 18:08:16 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "lem_in.h"

int			check_err(char *line, t_vert **graph, int n, int pos)
{
	if (n > 2 && *line != '#')
		return (-1);
	else if (ft_emptyline(line))
		return (-1);
	else if (*line != '#' && n != 2 && n != 0)
		error_handling(3, NULL, graph);
	else if ((pos == 1 || pos == 2) && n == 0)
		error_handling(pos, NULL, graph);
	return (1);
}

int			check_link(char *line)
{
	int w_amount;

	w_amount = 0;
	w_amount = ft_countchar(line, '-');
	if (w_amount != 1)
		return (-1);
	if (ft_strchr(line, ' '))
		return (-1);
	return (0);
}

void		check_s_e(int fd, char **line, t_vert **graph, int n)
{
	static int start;
	static int end;

	start = n == 1 ? start + 1 : start;
	end = n == 2 ? end + 1 : end;
	if (start > 1)
	{
		error_handling(1, NULL, graph);
	}
	else if (end > 1)
	{
		error_handling(2, NULL, graph);
	}
	free(*line);
	get_next_line(fd, line);
}
