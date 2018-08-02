/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 11:49:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/02 11:34:24 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H
# include <OpenCL/opencl.h>
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include "../frameworks/SDL2_ttf.framework/Headers/SDL_ttf.h"
# include "../frameworks/SDL2_image.framework/Headers/SDL_image.h"

enum	e_error {NUM_OF_ARG, ERROR, CAM_ERROR, LOAD_BMP_ERROR};
enum	e_figures {SPHERE, CYLINDER, CONE, PLANE, ELLIPSOID, TRIANGLE};
enum	e_lights {AMBIENT, POINT, DIRECT};

enum	e_object_data {RADIUS, POS_X, POS_Y, POS_Z, ANGLE_KOEF};
enum	e_buttons {LEFT1, LEFT2, LEFT3, LEFT4,
	RIGHT1, RIGHT2, RIGHT3, RIGHT4, NONE};
enum	e_foot_buttons {FILTERS, SAVE, ALIASING};
enum	e_filters {NOFILTER, SEPIA, GREYSCALE, NEGATIVE, PIXEL};
enum	e_gui{FIGURE_GUI, FOOT_GUI, FILTER_GUI, NO_GUI};
enum	e_axis{AXIS_X, AXIS_Y, AXIS_Z};

typedef struct			s_dot
{
	int					x;
	int					y;
}						t_dot;

typedef struct			s_channel
{
	int					red;
	int					green;
	int					blue;
}						t_channel;

typedef struct			s_ray
{
	cl_float3			origin;
	cl_float3			direction;
}						t_ray;

typedef struct			s_coord_sys
{
	cl_float3			b_x;
	cl_float3			b_y;
	cl_float3			b_z;
}						t_coord_sys;

typedef struct			s_camera
{
	cl_float3			origin;
	t_coord_sys			initial_basis;
	t_coord_sys			basis;
	cl_float3			angle_rot;
	int					is_set;
}						t_camera;

typedef struct			s_light
{
	int					type;
	float				intensity;
	cl_float3			origin;
	t_channel			color;
	cl_float3			direct;
	struct s_light		*next;
}						t_light;

typedef struct			s_cap
{
	float				dist;
	cl_float3			normal;
	t_coord_sys			basis;
	t_coord_sys			init_basis;
	cl_float3			angle_rot;
}						t_cap;

struct s_intersect;
typedef struct			s_objects
{
	int					type;
	int					texture_index;
	int					texture_repeat;
	int					is_cartoon;
	t_channel			color;
	float				radius;
	float				angle_coef;
	float				mirror_coef;
	float				transperent_coef;
	t_cap				cap[2];
	cl_float3			v0;
	cl_float3			v1;
	cl_float3			v2;
	cl_float3			origin;
	cl_float3			normal;
	cl_float3			axis_dimensions;
	t_coord_sys			basis;
	t_coord_sys			init_basis;
	cl_float3			angle_rot;
	int					bling_phong;
	struct s_objects	*next;
}						t_objects;

typedef struct			s_intersect
{
	float				distance;
	cl_float3			point;
	cl_float3			normal;
	t_objects			*fig;
	t_channel			texture_color;
}						t_intersect;

typedef struct			s_cl_data
{
	int					num_of_objects;
	int					num_of_lights;
	int					reflect_rate;
	int					max_reflections;
	int					trancparent_rate;
	int					max_trancparent;
	t_light				*current_lamp;
	SDL_Surface			**textures;
	t_camera			camera;
}						t_cl_data;

typedef struct			s_gui
{
	int					filter_gui;
	SDL_Rect			pos;
	TTF_Font			*c_font;
	TTF_Font			*open_sans;
	SDL_Surface			*bar;
	SDL_Rect			bar_pos;
	SDL_Surface			*arrow_left_active;
	SDL_Surface			*arrow_right_active;
	SDL_Surface			*arrow_left_unactive;
	SDL_Surface			*arrow_right_unactive;
	SDL_Surface			*little_text_area;
	SDL_Surface			*big_text_area;
	SDL_Rect			big_text_area_pos;
	SDL_Surface			*checked;
	SDL_Surface			*unchecked;
	SDL_Surface			*aliasing_on_foot;
	SDL_Surface			*aliasing_off_foot;
	SDL_Surface			*sepia;
	SDL_Surface			*greyscale;
	SDL_Surface			*pixel;
	SDL_Surface			*negative;
}						t_gui;

typedef struct			s_rt
{
	SDL_Window			*window;
	SDL_Surface			*screen_surface;
	t_gui				gui;
	int					aliasing;
	int					filter;
	int					take_screenshot;
	t_cl_data			cl_data;
	t_light				*lights;
	t_objects			*objects;
	t_light				*lights_arr;
	t_objects			*objects_arr;
	int					line_number;
	int					server_fd;
	int					server_mode;
	int					is_client;
}						t_rt;

typedef struct			s_thread_data
{
	t_rt				*scene;
	int					string_num;
}						t_thread_data;

typedef struct			s_parce
{
	char				*name;
	int					(*parce)(int, t_rt *);
}						t_parce;

#endif
