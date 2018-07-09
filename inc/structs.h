/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   structs.h                                          :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 16:13:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 18:03:24 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef STRUCTS_H
# define STRUCTS_H

enum	e_figures {SPHERE, CYLINDER, CONE, PLANE};
enum	e_lights {AMBIENT, SPOT};

typedef struct		s_dot
{
	int				x;
	int				y;
}					t_dot;

typedef struct		s_vector
{
	float			x;
	float			y;
	float			z;
}					t_vector;

typedef struct		s_channel
{
	float			red;
	float			green;
	float			blue;
}					t_channel;

typedef struct		s_coord_sys
{
	t_vector		b_x;
	t_vector		b_y;
	t_vector		b_z;
}					t_coord_sys;

typedef struct		s_cam
{
	t_vector		origin;
	t_coord_sys		basis;
}					t_cam;

typedef struct		s_light
{
	int				type;
	t_vector		origin;
	t_channel		color;
	float			brightness;
}					t_light;

typedef struct		s_ray
{
	t_vector		origin;
	t_vector		direction;
}					t_ray;

struct s_intersect;
typedef struct		s_figure
{
	int				type;
	t_channel		color;
	t_vector		origin;
	float			radius_or_cone_coef;
	t_coord_sys		basis;
	void			(*find_intersection)(t_ray, struct s_intersect*);
	t_vector		(*find_normal_to_figure)(struct s_figure*, t_vector);
	int				bling_phong;
}					t_figure;

typedef struct		s_intersect
{
	t_vector		point;
	float			distance;
	t_figure		*fig;
}					t_intersect;

typedef struct		s_scene_data
{
	SDL_Window		*window;
	SDL_Surface		*screen_surface;
	t_cam			camera;
	t_list			*lights;
	t_list			*figures;
}					t_scene_data;

typedef struct		s_thread_data
{
	t_scene_data	*scene;
	int				string_num;
}					t_thread_data;

#endif
