/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_structs.h                                       :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:03:55 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/12 19:04:01 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_STRUCTS_H
# define RT_STRUCTS_H

typedef struct	s_vector
{
	double x;
	double y;
	double z;
}				t_vector;

typedef struct	s_ray
{
	t_vector	origin;
	t_vector	direct;
	// t_vector	rev_dir;
	// double		dest;
	// int			id;
	// int			main_col;
	// int			mirror;
 //    int         transperent;
}				t_ray;

typedef struct	s_camera
{
	t_vector	origin;
	t_vector	direct;
	t_vector	up;
	t_vector	right;
	int			is_set;
	double		dest;
}				t_camera;

// typedef struct	s_sphere
// {
// 	int			color;
// 	t_vector	centre;
// 	int			id;
// 	double		radius;
// 	int			mirror;
//     int         transperent;
// }				t_sphere;

typedef struct	s_light
{
	char			is_dir;
	t_vector		direct;
	int				color;
	double			intence;
	struct s_light	*next;
}				t_light;

// typedef struct	s_plane
// {
// 	t_vector	normal;
// 	t_vector	point;
// 	int			id;
// 	int			color;
// 	int			mirror;
//     int         transperent;
// }				t_plane;

// typedef struct	s_cone
// {
// 	t_vector	direct;
// 	t_vector	point;
// 	double		ang;
// 	int			id;
// 	int			color;
// 	int			mirror;
//     int         transperent;
// }				t_cone;

// typedef struct	s_cylinder
// {
// 	t_vector	direct;
// 	t_vector	point;
// 	double		radius;
// 	int			id;
// 	int			color;
// 	int			mirror;
//     int         transperent;
// }				t_cylinder;

typedef struct	s_shape t_shape;

typedef struct	s_intersected
{
	t_shape		*shape;
	t_vector	intersect_point;
	double		distance;
}				t_intersected;

typedef struct	s_rt
{
	void			*mlx;
	void			*win;
	void			*img;
	t_shape			*shapes;
	t_light			*light;
	t_camera		camera;
	t_intersected	intersected;
	int				reflect_rate;
	int				max_reflections;
	int				line_number;
}				t_rt;

typedef struct	s_shape
{
	char			name;
	int				id;
	t_vector		direct;
	t_vector		origin;
	t_vector		normal;
	double			radius;
	double			angle_coef;
	int				color;
	int				mirror_coref;
	int				transperent_coef;
	double			(*find_distance)(t_ray *, t_shape *, t_rt *);
	double			(*make_shading)(t_ray *, t_shape *, t_rt *);
	struct s_shape	*next;
}				t_shape;

typedef struct	s_parce
{
	char		*name;
	int			(*parce)(int, t_rt *, int);
}				t_parce;

#endif
