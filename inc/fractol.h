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
# include <unistd.h>
# include <sys/types.h>
# include <unistd.h>
# include <errno.h>

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

/* Input Event Masks. Used as event-mask window attribute and as arguments
   to Grab requests.  Not to be confused with event names.  */

#define NoEventMask			0L
#define KeyPressMask			(1L<<0)  
#define KeyReleaseMask			(1L<<1)  
#define ButtonPressMask			(1L<<2)
#define ButtonReleaseMask		(1L<<3)  
#define EnterWindowMask			(1L<<4)  
#define LeaveWindowMask			(1L<<5)  
#define PointerMotionMask		(1L<<6)  
#define PointerMotionHintMask		(1L<<7)  
#define Button1MotionMask		(1L<<8)  
#define Button2MotionMask		(1L<<9)  
#define Button3MotionMask		(1L<<10) 
#define Button4MotionMask		(1L<<11) 
#define Button5MotionMask		(1L<<12) 
#define ButtonMotionMask		(1L<<13) 
#define KeymapStateMask			(1L<<14)
#define ExposureMask			(1L<<15) 
#define VisibilityChangeMask		(1L<<16) 
#define StructureNotifyMask		(1L<<17) 
#define ResizeRedirectMask		(1L<<18) 
#define SubstructureNotifyMask		(1L<<19) 
#define SubstructureRedirectMask	(1L<<20) 
#define FocusChangeMask			(1L<<21) 
#define PropertyChangeMask		(1L<<22) 
#define ColormapChangeMask		(1L<<23) 
#define OwnerGrabButtonMask		(1L<<24) 

/* Event names.  Used in "type" field in XEvent structures.  Not to be
confused with event masks above.  They start from 2 because 0 and 1
are reserved in the protocol for errors and replies. */

#define KeyPress		2
#define KeyRelease		3
#define ButtonPress		4
#define ButtonRelease		5
#define MotionNotify		6
#define EnterNotify		7
#define LeaveNotify		8
#define FocusIn			9
#define FocusOut		10
#define KeymapNotify		11
#define Expose			12
#define GraphicsExpose		13
#define NoExpose		14
#define VisibilityNotify	15
#define CreateNotify		16
#define DestroyNotify		17
#define UnmapNotify		18
#define MapNotify		19
#define MapRequest		20
#define ReparentNotify		21
#define ConfigureNotify		22
#define ConfigureRequest	23
#define GravityNotify		24
#define ResizeRequest		25
#define CirculateNotify		26
#define CirculateRequest	27
#define PropertyNotify		28
#define SelectionClear		29
#define SelectionRequest	30
#define SelectionNotify		31
#define ColormapNotify		32
#define ClientMessage		33
#define MappingNotify		34
#define GenericEvent		35
#define LASTEvent		36

# define WIN_W 1000
# define WIN_H 800

# define NUM_OF_THREADS 20

# define MAX_WIND_NUM 2

typedef double	t_rot_mat[4][4];

typedef struct	s_complex_number
{
	double			r;
	double			i;
}				t_complex;

typedef struct	s_image
{
	int				bit_pixel;
	int				line_size;
	int				endian;
	void			*img_ptr;
	char			*pix_ptr;
}				t_image;

typedef struct	s_window
{
	int 			*num_of_wind;
	void			*mlx;
	void			*win;
	t_image			*img;
	t_rot_mat		*rot;
	void			*(*fract_foo)(void *param);
	int				line_per_thread;
}				t_window;

typedef struct	s_thread
{
	int				*y;
	t_window		*wind;
	int				num;
	pthread_t		des;
}				t_thread;

typedef struct	s_mlx
{
	void			*mlx;
	t_window		*wind[MAX_WIND_NUM];
	t_thread		thread[NUM_OF_THREADS];
}				t_mlx;

void			*potok(void *param);

int				expose_hook(void *param);
int				mouse_hook(int but, int x, int y, void *param);
int				mouse_move_hook(int x, int y, void *param);
int				key_hook(int key, void *param);
int				leave_hook(void *param);

void			*maldelbort(void *param);

void			img_pixel_put(t_image *data, int x, int y, int color);
void			print_fractl(t_window wind, t_rot_mat rot);
int				check_input(int argc, char **argv);

#endif
