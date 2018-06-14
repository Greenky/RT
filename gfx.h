/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gfx.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:03:55 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/12 19:04:01 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef GFX_H
# define GFX_H
# include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include "get_next_line.h"
# define SCR_SIZE 1000
# define OBJ_NUM 6
# define MAX_LEN 99999999
# define ESC 53

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
	t_vector	rev_dir;
	double		dest;
	int			id;
	int			main_col;
	int			mirror;
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

typedef struct	s_sphere
{
	int			color;
	t_vector	centre;
	int			id;
	double		radius;
	int			mirror;
}				t_sphere;

typedef struct	s_light
{
	char			is_dir;
	t_vector		direct;
	int				color;
	double			intence;
	struct s_light	*next;
}				t_light;

typedef struct	s_plane
{
	t_vector	normal;
	t_vector	point;
	int			id;
	int			color;
	int			mirror;
}				t_plane;

typedef struct	s_cone
{
	t_vector	direct;
	t_vector	point;
	double		ang;
	int			id;
	int			color;
	int			mirror;
}				t_cone;

typedef struct	s_cylinder
{
	t_vector	direct;
	t_vector	point;
	double		radius;
	int			id;
	int			color;
	int			mirror;
}				t_cylinder;

typedef struct	s_shape
{
	char			name;
	int				id;
	void			*shape;
	double			(*inter)(t_ray *, void *, t_light *, struct s_shape *);
	struct s_shape	*next;
}				t_shape;

typedef struct	s_parce
{
	char		*name;
	int			(*parce)(int, int*, void**, int);
}				t_parce;

typedef struct	s_grafx
{
	void		*mlx;
	void		*win;
	void		*img;
	t_shape		**shapes;
	t_light		**light;
	t_camera	*camera;
	double		x;
	double		y;
	int			l_num;
}				t_grafx;

void			add_shape(t_shape **sh, void *shape, char name, int id);
void			ray_casting(t_grafx *gfx, t_shape *shape_list, t_light *light,
t_camera camera);
double			v_mod(t_vector v);
t_vector		set_vector(double x, double y, double z);
t_vector		v_to_len(t_vector v, double len, int norm);
t_vector		add_vectors(t_vector v1, t_vector v2);
t_vector		sub_vectors(t_vector v1, t_vector v2);
t_vector		vec_dob(t_vector v1, t_vector v2);
double			scalar_dob(t_vector v1, t_vector v2);
int				light_calculate(t_vector nor, t_ray s_ray, t_light *light,
t_shape *sh);
void			error_caster(int line_number, char *s1, char *s2);
int				begin_with(char *line, char *begin);
char			*trim_from(char *line, int i);
double			str_to_double(char *line, int i, int l_num);
int				parce_color(char *line, int l_num);
t_vector		parce_vector(char *line, int l_num);
int				sphere_parce(int fd, int *l_num, void **shape_list, int id);
int				cone_parce(int fd, int *l_num, void **shape_list, int id);
int				cylin_parce(int fd, int *l_num, void **shape_list, int id);
int				plane_parce(int fd, int *l_num, void **shape_list, int id);
double			intersect_cone(t_ray *ray, void *con, t_light *light,
t_shape *sh);
double			intersect_cylinder(t_ray *ray, void *cy, t_light *light,
t_shape *sh);
double			intersect_plane(t_ray *ray, void *pl, t_light *light,
t_shape *sh);
double			intersect_sphere(t_ray *ray, void *sf, t_light *light,
t_shape *sh);
int				light_parce(int fd, int *l_num, void **light_list, int n);
int				light_calculate(t_vector nor, t_ray s_ray, t_light *light,
t_shape *sh);
void			file_parcing(int fd, t_grafx *gfx);
void			freesher(t_light **light, t_shape **sh);
int				cam_parce(int fd, int *l_num, t_camera *camera);
int				color_add(int first, int second);
// int				zercal_light(t_ray ray, t_shape *sh, t_light *li, t_vector r);

#endif
