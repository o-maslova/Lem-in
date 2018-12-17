/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   view.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:08:46 by omaslova          #+#    #+#             */
/*   Updated: 2018/11/24 14:08:53 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VIEW_H
# define VIEW_H

# include <stdio.h>
# include <mlx.h>
# include <math.h>
# include "../lem_in.h"

# define WIDTH 1000
# define HEIGTH 1000
# define CELL_SIZE 10
# define POS(x) (x >= 0 ? 1 : -1)
# define MAX(x, y) ((x) > (y)) ? (x) : (y)

int					my_fd;

typedef struct		s_brzhm
{
	int				d_x;
	int				d_y;
	int				len_x;
	int				len_y;
	int				length;
	int				err;
}					t_brzhm;

typedef struct		s_win
{
	int				width;
	int				heigth;
	t_brzhm			*var;
	int				mtrx_size;
	int				cell;
	int				value;
	int				size_line;
	int				endian;
	int				bpp;
	char			*img;
	void			*win_ptr;
	void			*mlx_ptr;
	void			*img_ptr;
}					t_win;

// int					list_fulling(t_vert **graph, char **line, int pos);
// int					making_links(char *line, t_vert **graph, int **links);
void				init(t_win *win);
void				pixel_put_img(t_win *win, int x, int y, int colour);
void				brznh_algo(t_win *win, t_vert start, t_vert end);

int					allocate_mem(t_win *win, char *line, int i);
int					set_matrix(t_win *win);
void				define_values(t_win *win);
void				draw_field(t_win *win);
void				draw_players(t_win *win);
void				display_winner(t_win *win, char *line);

#endif
