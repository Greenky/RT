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
	cl_float3	origin;
	cl_float3	direction;
}				t_ray;

typedef struct		s_coord_sys
{
	cl_float3		b_x;
	cl_float3		b_y;
	cl_float3		b_z;
}					t_coord_sys;

typedef struct	s_camera
{
	cl_float3		origin;
	t_coord_sys		initial_basis;
	t_coord_sys		basis;
	cl_float3		angle_rot;
	int				is_set;

	double			dest;//TODO delete if unnecessary
}				t_camera;

typedef struct		s_light // ADDED TYPE, fix
{
	int				type;
	float			intensity;
	cl_float3		origin;
	t_channel		color;
	cl_float3		direct;
	struct s_light	*next;
}					t_light;

struct s_intersect;
typedef struct		s_objects
{
	int					type;
	int 				texture_index;
	int 				is_cartoon;
	t_channel			color;
	float				radius;
	float				angle_coef;
	float				mirror_coef;
	float				transperent_coef;
	cl_float3			origin;
	cl_float3			normal;
	cl_float3			axis_dimensions;//размеры осей x y z для эллипсоида
	t_coord_sys			basis;
	int					bling_phong;
	struct s_objects	*next;
}					t_objects;

typedef struct		s_intersect
{
	float			distance;
	cl_float3		point;//точка пересечения фигуры и луча
	cl_float3		normal;
	t_objects		*fig;
	t_channel		texture_color;
}					t_intersect;

typedef struct	s_cl_data
{
	int				num_of_objects;
	int				num_of_lights;
	int				reflect_rate;
	int				max_reflections;
	SDL_Surface		**textures; // NEW VARIABLE
	t_camera		camera;
}				t_cl_data;

typedef struct		s_cl
{
	cl_device_id		device_id;
	cl_context			context;
	cl_command_queue	queue;
	cl_program			program;
	cl_kernel			kernel;
	cl_platform_id		platform_id;
	cl_uint				devices_num;
	cl_uint				platforms_num;
	size_t				local_size;
	size_t				global_size;
	cl_int				err;
	cl_mem				lights;
	cl_mem				objects;
	cl_mem				image;
}						t_cl;

typedef struct	s_rt
{
	SDL_Window		*window;
	SDL_Surface		*screen_surface;
//	t_camera		camera;
	t_cl			cl;
	t_cl_data		cl_data;
	t_light			*lights;
	t_objects		*objects;
	t_light			*lights_arr; // масив для CL
	t_objects		*objects_arr; // масив для CL
//	int				objects_num;
//	int				lights_num;
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
