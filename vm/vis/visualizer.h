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

# include <mlx.h>
# include "libft.h"

# define KEK				18

/*
**	TEXTURES
*/
# define NUM_SMBLS_MINI		2371
# define NUM_SMBLS_PICTURE	13390628
# define SIDE_PICTURE		1286
# define WARCRAFT_SQUARE	18

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
# define SIDE_SQUARE		vis->side_square
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
# define SIZE_FIELD_X		vis->win->size_field_x
# define SIZE_FIELD_Y 		((INDENT_SQUARE_Y * 2) + (FIELD_SIDE * SIDE_SQ_WID))

/*
**	LEGEND
*/
# define NO_FRAME			SIZE_MENU - FRAME_WIDTH
# define INDENT_LEGEND_X	SIZE_FIELD_X - SIZE_MENU + FRAME_WIDTH + LETER_X * 3
# define LEGEND_INDENT_Y	SIZE_FIELD_Y / 20
# define LINE_WIDTH			(SIZE_FIELD_Y - FRAME_WIDTH * 2) / 15
# define LOG_SCALE_X		(SIZE_FIELD_X - (NO_FRAME) / LETER_X * 7 + LETER_X)
# define CYCLE_X			SIZE_FIELD_X - (SIZE_MENU - FRAME_WIDTH * 2) / 5 * 3

/*
**	COLORS
*/
# define RGB_LIGHT_GREEN	0xCCCC00
# define RGB_GREEN			0x00FF00
# define RGB_BLACK			0x000000
# define RGB_WHITE			0xFFFFFF
# define RGB_CYAN			0x00FFFF
# define RGB_BLUE			0x000080
# define RGB_RED			0xFF0000
# define RGB_GRAY			0xA0A0A0
# define PLAYER_1			RGB_RED
# define PLAYER_2			RGB_BLUE
# define PLAYER_3			RGB_GREEN
# define PLAYER_4			RGB_CYAN

/*
**	KEYCODES
*/
# define ARROW_RIGHT		124
# define ARROW_LEFT			123
# define B_SPACE			49
# define RETURN				36
# define EXIT				53

/*
**	SHORT CUTS
*/
# define WIN				vis->win
# define SQ					vis->sq
# define TML				vis->log_scale
# define BACKLOG			vis->backlog
# define PICTURES			vis->pictures
# define PLAYERS			vis->players

typedef struct				s_window
{
	void					*mlx;
	void					*win;
	void					*image;
	int						*data;
	int						size_field_x;
}							t_window;

typedef struct				s_square
{
	int						x;
	int						y;
	int						num_sq;
}							t_square;

typedef struct				s_log_scale
{
	int						log_scale_position;
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

typedef struct				s_players
{
	int						occupied_cells[4];
	int						percents[4];
	int						players_colors[4];
}							t_players;

typedef struct				s_visualizer
{
	t_window				*win;
	t_square				*sq;
	t_log_scale				*log_scale;
	t_list					*backlog;
	t_pictures				pictures;
	t_players				players;
	char					side_square;
	char					n_players;
	char					loop_key;
	int						cycle;
	int						num_logs;
}							t_visualizer;

/*
**		HOOKS
*/
int							key_press(int keycode, void *param);
int							auto_draw(void *param);
/*
**		BASIK DRAW
*/
void						draw_horizontal_line(t_visualizer *vis, int x_y[2],
								int length, int color);
void						draw_vertical_line(t_visualizer *vis, int x_y[2],
								int length, int color);
void						clear_area(t_visualizer *vis, int x, int y);
/*
**		MENU
*/
void						draw_menu(t_visualizer *vis);
void						draw_frame(t_visualizer *vis);
void						draw_legend(t_visualizer *vis);
void						draw_cycle(t_visualizer *vis);
void						draw_percent(t_visualizer *vis);
void						draw_instructions(t_visualizer *vis);
void						draw_log_scale(t_visualizer *vis, int move);
void						draw_log_scale_uptoend(t_visualizer *vis,
								int color);
void						draw_press_enter(t_visualizer *vis);
int							draw_winner(t_visualizer *vis, int winer);
/*
**		FIELD
*/
void						draw_square(t_visualizer *vis, int num_player);
void						draw_cursor(t_visualizer *vis, int position,
								int id);
void						wipe_off_cursor(t_visualizer *vis, int position);
int							rand_put_pixel(t_visualizer *vis, int *picture);
/*
**		LOG OPERATIONS
*/
void						move_log_back(t_visualizer *vis);
void						move_log_front(t_visualizer *vis);
void						add_log(t_visualizer *vis);
/*
**		TEXTURES
*/
int							*get_final_picture(int player);
int							*get_picture(t_visualizer *vis, int num_player);
int							*get_player1(t_visualizer *vis);
int							*get_player2(t_visualizer *vis);
int							*get_player3(t_visualizer *vis);
int							*get_player4(t_visualizer *vis);
int							*get_alliance();
int							*get_horde();
int							*get_undead();
int							*get_elf();
/*
**		COORDINATES
*/
void						x_y_square(t_visualizer *vis, int num_sq);
int							get_num_player(t_visualizer *vis, int x, int y);
int							get_num_pixel(t_visualizer *vis, int x, int y);

#endif
