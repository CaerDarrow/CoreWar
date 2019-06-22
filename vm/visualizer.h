/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   visualizer.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: gleonett <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2019/05/30 12:48:16 by gleonett          #+#    #+#             */
/*   Updated: 2019/05/30 12:48:18 by gleonett         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VISUALIZER_H
# define VISUALIZER_H

# include <fcntl.h>
# include <mlx.h>
# include <math.h>
# include "libft.h"

# define SIDE_PICTURE		1286
/*
**	LOGS
*/
# define NUM_LOGS 256
/*
**	LETER
*/
# define LETER_X			10
# define LETER_Y			25
/*
**	GRID
*/
# define GRID_WIDTH			2
/*
**	SQUARE
*/
# define SIDE_SQUARE		entity->vis->side_square
# define SIDE_SQ_WID		(SIDE_SQUARE + GRID_WIDTH)
/*
**	FRAME
*/
# define SIZE_MENU			300
# define FRAME_WIDTH		SIZE_MENU / 50
/*
**	FIELD
*/
# define FIELD_SIDE			64
# define INDENT_SQUARE_X	4
# define INDENT_SQUARE_Y	4
# define SIZE_FIELD_X		entity->vis->win->size_field_x
# define SIZE_FIELD_Y 		((INDENT_SQUARE_Y * 2) + (FIELD_SIDE * SIDE_SQ_WID))
/*
**	LEGEND
*/
# define LOG_SCALE_X		(SIZE_FIELD_X - (SIZE_MENU - FRAME_WIDTH) \
								/ LETER_X * 7 + LETER_X * 1)
# define INDENT_LEGEND_X	SIZE_FIELD_X - SIZE_MENU + FRAME_WIDTH + LETER_X * 3
# define LEGEND_INDENT_Y	SIZE_FIELD_Y / 20
# define LINE_WIDTH			(SIZE_FIELD_Y - FRAME_WIDTH * 2) / 15
# define CYCLE_X			SIZE_FIELD_X - ((SIZE_MENU - FRAME_WIDTH * 2) / 5 * 3)
/*
**	COLORS
*/
# define RGB_LIGHT_GREEN	0xCCCC00
# define RGB_YELLOW			0xFFFF00
# define RGB_PURPLE			0xA000A0
# define RGB_GREEN			0x00FF00
# define RGB_BLACK			0x000000
# define RGB_WHITE			0xFFFFFF
# define RGB_CYAN			0x00FFFF
# define RGB_BLUE			0x000080
# define RGB_PINK			0xFF69B4
# define RGB_RED			0xFF0000
# define RGB_GRAY			0xA0A0A0
# define PLAYER_1			RGB_RED
# define PLAYER_2			RGB_BLUE
# define PLAYER_3			RGB_GREEN
# define PLAYER_4			RGB_CYAN
/*
**	keycodes
*/
# define ARROW_RIGHT		124
# define ARROW_LEFT			123
# define B_SPACE			49
# define RETURN				36
# define EXIT				53
/*
**	SHORT CUTS
*/
# define VIS				entity->vis
# define WIN				entity->vis->win
# define SQ					entity->vis->sq
# define TML				entity->vis->log_scale
# define BACKLOG			entity->vis->backlog
# define PICTURES			entity->vis->pictures

typedef struct				s_window
{
	void					*mlx;
	void					*win;
	void					*image;
	int 					*data;
	int 					size_field_x;
}							t_window;

typedef struct				s_square
{
	int						x;
	int						y;
	int 					num_sq;
}							t_square;

typedef struct				s_log_scale
{
	int						log_scale_position;
	int						const_move;
}							t_log_scale;

typedef struct				s_pictures
{
	int						*player1;
	int						*player2;
	int						*player3;
	int						*player4;
}							t_pictures;

typedef struct				s_log
{
	int						cycle;
	int						*data;
	int						percents[4];
}							t_log;

typedef struct				s_visualizer
{
	t_window				*win;
	t_square				*sq;
	t_log_scale				*log_scale;
	t_list					*backlog;
	t_pictures				pictures;
	char 					side_square;
	int						num_logs;
	char 					loop_key;
	int 					occupied_cells[4];
	int 					percents[4];
	int						players_colors[4];
}							t_visualizer;
/*
**		basik
*/
int					auto_draw_square(void *param);
/*
**		hooks
*/
int					key_press(int keycode, void *param);
/*
**		pictures
*/
int					*get_alliance();
int					*get_horde();
int					*get_undead();
int					*get_elf();

#endif