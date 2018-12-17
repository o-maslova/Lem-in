/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   display_staff.c                                    :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: omaslova <omaslova@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/11/24 14:08:09 by omaslova          #+#    #+#             */
/*   Updated: 2018/11/24 14:08:14 by omaslova         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "view.h"

void	draw_players(t_win *win)
{
	mlx_string_put(win->mlx_ptr, win->win_ptr, PAD, PAD,
	0xFFD700, "Your player is ");
	mlx_string_put(win->mlx_ptr, win->win_ptr, PAD + 150, PAD,
	0xF68A41, "orange");
	mlx_string_put(win->mlx_ptr, win->win_ptr, PAD, PAD + 30,
	0xFFD700, "Enemy player is ");
	mlx_string_put(win->mlx_ptr, win->win_ptr, PAD + 160, PAD + 30,
	0x859A14, "green");
	mlx_string_put(win->mlx_ptr, win->win_ptr, WIDTH - 200, HEIGTH - 50,
	0xFF0000, "omaslova.filler");
}

void	you_win(t_win *win)
{
	char	*my_score;
	char	*enemy_score;

	my_score = ft_itoa(win->my_score);
	enemy_score = ft_itoa(win->enemy_score);
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION - 40,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 20, 0xFFD700, "Your score: ");
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION + 100,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 20, 0xFFD700, my_score);
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION - 40,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 40, 0xFFD700, "Enemy score: ");
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION + 110,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 40, 0xFFD700, enemy_score);
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 60, 0x00FF00, "YOU WIN!");
	system("say you, win");
}

void	you_lose(t_win *win)
{
	char	*my_score;
	char	*enemy_score;

	my_score = ft_itoa(win->my_score);
	enemy_score = ft_itoa(win->enemy_score);
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION - 40,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 20, 0xFFD700, "Your score: ");
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION + 100,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 20, 0xFFD700, my_score);
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION - 40,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 40, 0xFFD700, "Enemy score: ");
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION + 110,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 40, 0xFFD700, enemy_score);
	mlx_string_put(win->mlx_ptr, win->win_ptr, POSITION,
	VIEW_ROW * CELL_SIZE + (PAD * VAL) + 60, 0xFF0000, "YOU LOSE!");
	system("say you, lose");
}

void	display_winner(t_win *win, char *line)
{
	char	*tmp;

	get_next_line(g_fd_m, &tmp);
	if (ft_tolower(*(line + 3)) == g_player)
	{
		win->my_score = ft_atoi(line + 10);
		win->enemy_score = ft_atoi(tmp + 10);
		if (win->my_score > win->enemy_score)
			you_win(win);
		else
			you_lose(win);
	}
	else
	{
		win->enemy_score = ft_atoi(line + 10);
		win->my_score = ft_atoi(tmp + 10);
		if (win->enemy_score < win->my_score)
			you_win(win);
		else
			you_lose(win);
	}
	free(tmp);
}
