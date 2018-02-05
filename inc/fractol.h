/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   fractol.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: afokin <marvin@42.fr>                      +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/02/02 14:46:15 by afokin            #+#    #+#             */
/*   Updated: 2018/02/02 14:46:19 by afokin           ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef FRACTOL_H
# define FRACTOL_H
# include "stdio.h"
# include <mlx.h>
# include <pthread.h>
# include <stdlib.h>

# define ESC 53
# define RIGHT_ERROW 123
# define LEFT_ERROW 124
# define UP_ERROW 126
# define DOWN_ERROW 125
# define MINUS 78
# define PLUS 69
# define ONE 18
# define TWO 19
# define Q_KEY 12
# define W_KEY 13
# define E_KEY 14
# define A_KEY 0
# define S_KEY 1
# define D_KEY 2
# define SPASE 49

# define WIN_W 800
# define WIN_H 800

typedef double	t_rot_mat[4][4]; 

typedef struct	s_complex_number
{
	double			r;
	double			i;
}				t_complex;

typedef struct	s_image
{
	void			*img_ptr;
	char			*pix_ptr;
	int				bit_pixel;
	int				line_size;
	int				endian;
}				t_image;

typedef struct	s_window
{
	void			*mlx;
	void			*win;
	t_image			*img;
	t_rot_mat		*rot;
}				t_window;


void			*potok(void *param);
int				expose_hook(void *param);
int				mouse_hook(int but, int x, int y, void *param);
void			img_pixel_put(t_image *data, int x, int y, int color);
int				key_hook(int key, void *param);
void			print_fractl(t_window wind, t_rot_mat rot);

#endif
