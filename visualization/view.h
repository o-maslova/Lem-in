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

# define WIDTH 500
# define HEIGTH 500
# define MOVE_SIDE win->move_side
# define MOVE_UP win->move_up
# define CELL_SIZE win->cell
# define RIGHT_DOT win->right->x
# define COLOR 0xFF0000
// # define SCALE 
# define POS(x) (x >= 0 ? 1 : -1)
# define MAX(x, y) ((x) > (y)) ? (x) : (y)

int					my_fd;

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

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
	int				**links;
	int				min_up;
	int				min_down;
	int				min_left;
	int				min_right;
	t_vert			*graph;
	t_brzhm			*var;
	int				mtrx_size;
	int				cell;
	int				move_side;
	int				move_up;
	int				value;
	void			*win_ptr;
	void			*mlx_ptr;
}					t_win;

void				init(t_win **win);
void				matrix_to_default(int **links);
void				pixel_put_img(t_win *win, int x, int y, int colour);
void				brznh_algo(t_win *win, t_dot start, t_dot end);
void				drawWuLine(t_win *win, t_dot start, t_dot end);
void				draw_anthill(t_win *win, t_vert *graph, int **links);
t_dot				search_by_pos(t_vert *graph, int pos);

#endif
