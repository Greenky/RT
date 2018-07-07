/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_data.h                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/01/12 19:03:55 by vmazurok          #+#    #+#             */
/*   Updated: 2018/01/12 19:04:01 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef rt_data_H
# define rt_data_H
// # include <mlx.h>
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <pthread.h>
# include <stdio.h>
# include <errno.h>
# include "get_next_line.h"
# include "rt_structs.h"
# define SCR_SIZE 1000
# define OBJ_NUM 6
# define MAX_LEN 99999999
# define ESC 53
# define LEFT_ARROW 123
# define RIGHT_ARROW 124
# define UP_ARROW 126
# define DOWN_ARROW 125
# define PLUS 24
# define MINUS 27

void			add_shape(t_rt *rt_data, t_shape *shape);

void			ray_casting(t_rt *rt_data);

double			v_mod(t_vector v);
t_vector		set_vector(double x, double y, double z);
t_vector		v_to_len(t_vector v, double len, int norm);
t_vector		add_vectors(t_vector v1, t_vector v2);
t_vector		sub_vectors(t_vector v1, t_vector v2);
t_vector		vec_dob(t_vector v1, t_vector v2);
double			scalar_dob(t_vector v1, t_vector v2);
int				shading_calculation(t_vector nor, t_ray ray, t_rt *rt_data);
int				color_add(int first, int second);

void			error_caster(int line_number, char *s1, char *s2);

void			file_parcing(int fd, t_rt *rt_data);
int				begin_with(char *line, char *begin);
char			*trim_from(char *line, int i);
double			str_to_double(char *line, int i, int line_number);
int				parce_color(char *line, int line_number);
t_vector		parce_vector(char *line, int line_number);
void			freesher(t_light *light, t_shape *sh);


int				cam_parce(int fd, t_rt *rt_data, int id);
int				light_parce(int fd, t_rt *rt_data, int id);
int				sphere_parce(int fd, t_rt *rt_data, int id);
int				cone_parce(int fd, t_rt *rt_data, int id);
int				cylin_parce(int fd, t_rt *rt_data, int id);
int				plane_parce(int fd, t_rt *rt_data, int id);

double			distance_to_sphere(t_ray ray, t_shape *sphere);
double			distance_to_cone(t_ray ray, t_shape *sphere);
double			distance_to_cylinder(t_ray ray, t_shape *sphere);
double			distance_to_plane(t_ray ray, t_shape *sphere);

t_vector		normal_to_sphere(t_ray ray, t_intersected intersected);
t_vector		normal_to_cone(t_ray ray, t_intersected intersected);
t_vector		normal_to_cylinder(t_ray ray, t_intersected intersected);
t_vector		normal_to_plane(t_ray ray, t_intersected intersected);
// int				zercal_light(t_ray ray, t_shape *sh, t_light *li, t_vector r);

#endif
