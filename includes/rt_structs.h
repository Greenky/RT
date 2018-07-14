/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 11:49:00 by vpaladii          #+#    #+#             */
/*   Updated: 2018/07/07 11:49:00 by vpaladii         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

enum	e_error {NUM_OF_ARG, ERROR, CAM_ERROR};
enum	e_figures {SPHERE, CYLINDER, CONE, PLANE, ELLIPSOID};
enum	e_lights {AMBIENT, POINT, DIRECT};

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

typedef struct	s_ray
{
	t_vector	origin;
	t_vector	direction;
}				t_ray;

typedef struct		s_coord_sys
{
	t_vector		b_x;
	t_vector		b_y;
	t_vector		b_z;
}					t_coord_sys;

typedef struct	s_camera
{
	t_vector		origin;
	t_coord_sys		initial_basis;
	t_coord_sys		basis;
	t_vector		angle_rot;
	int			    is_set;

	double		    dest;//TODO delete if unnecessary

}				t_camera;

typedef struct		s_light // ADDED TYPE, fix
{
	int				type;
	t_vector		origin;
	t_channel		color;
	float			intensity;
	t_vector		direct;
	struct s_light	*next;
}					t_light;

struct s_intersect;
typedef struct		s_objects
{
	int					type;
	t_channel			color;
	t_vector			origin;
    t_vector			normal;
	float				radius;
    float				angle_coef;
	t_coord_sys			basis;
	float				mirror_coef;
	float				transperent_coef;
	t_vector			axis_dimensions;//размеры осей x y z для эллипсоида
	int					bling_phong;
	struct s_objects	*next;
}					t_objects;

typedef struct		s_intersect
{
	t_vector	    point;//точка пересечения фигуры и луча
	float			distance;
	t_objects		*fig;
	t_vector		normal;
}					t_intersect;

typedef struct	s_rt
{
	SDL_Window		*window;
	SDL_Surface		*screen_surface;
	t_camera		camera;
	t_light			*lights;
	t_objects		*objects;
	t_light			*lights_arr; // масив для CL
	t_objects		*objects_arr; // масив для CL
	int				objects_num;
	int				lights_num;
	int				reflect_rate;
	int				max_reflections;
	int				line_number;
}				t_rt;

typedef struct	s_parce
{
	char		*name;
	int			(*parce)(int, t_rt *);
}				t_parce;

#endif
