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

# define WIN_W 800
# define WIN_H 800

typedef struct	s_complex_number
{
	int				r;
	int				i;
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
}				t_widow;



#endif
