/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:03:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/07/07 12:03:00 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

# ifndef RT_FUNCTIONS_H
# define RT_FUNCTIONS_H

// Windows - # include <SDL2/SDL.h>
# include "../frameworks/SDL2.framework/Headers/SDL.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include "rt_structs.h"

# define FALSE 0
# define TRUE 1
# define SCR_SIZE 800
# define OBJ_NUM 6
# define DISTANCE 1
# define DIRECT_LIGHT_IS_PARSED 15
# define POINT_LIGHT_IS_PARSED 23
# define AMBIENT_LIGHT_IS_PARSED 35
# define SPHERE_IS_PARSED 15
# define CAMERA_IS_PARSED 3
# define CONE_IS_PARSED 15
# define CYLINDER_IS_PARSED 15
# define PLANE_IS_PARSED 15
# define STEP (1.0 / SCR_SIZE)
# define LEFT_BOUND (-(SCR_SIZE / 2))
# define TOP_BOUND (-(SCR_SIZE / 2))
# define A 0
# define B 1
# define C 2
# define ANGLE (M_PI * (5) / 180.0)
# define ANGLE_IN_DEGREES(angle) (M_PI * (angle) / 180.0)

# define VEC(a1, a2, a3) (t_vector){a1, a2, a3}
# define W_TITLE "RT by BOBMA_RAKETA"


/*validate directory*/
int				find_fd(char *file);
/*parcing_function directory*/
void			file_parcing(char *file, t_rt *rt_data);
void			line_reader(t_rt *rt_data, int fd, const t_parce arr[]);
void			parcer_functions(char **str, t_rt *rt_data, const t_parce arr[],
							 int fd);
void			correct_plane_normal(t_rt *rt_data);
t_coord_sys		create_coord_system(t_coord_sys basis);

int				cam_parce(int fd, t_rt *rt_data);
void			camera_data_fill(char **line, t_camera *camera, int l_num, int *flag);

int				cone_parce(int fd, t_rt *rt_data);
void			cone_data_fill(char **line, t_objects *cone, int l_num, int *flag);
void			more_cone_data_fill(char **line, t_objects *cone, int l_num, int *flag);

int				cylinder_parce(int fd, t_rt *rt_data);
void			cylin_data_fill(char **line, t_objects *cyl, int l_num, int *flag);
void			more_cylin_data_fill(char **line, t_objects *cyl, int l_num, int *flag);

int				sphere_parce(int fd, t_rt *rt_data);
void			sphere_fill(char **line, t_objects *sphere, int l_num, int *flag);

int				plane_parce(int fd, t_rt *rt_data);
void			plane_fill(char **line, t_objects *plane, int l_num, int *flag);

void			add_shape(t_rt *rt_data, t_objects *shape);
void			add_light(t_rt *rt_data, t_light *light);

int				begin_with(char *line, char *begin);
char			*trim_from(char *line, int i);

float			drob_finder(char *line, int i, int line_number);
float			str_to_float(char *line, int i, int line_number);

t_channel		parce_color(char *line, int line_number);
float			float_finder(char *line, int *i, int line_number);
t_vector		parce_vector(char *line, int line_number);

int				light_parce(int fd, t_rt *rt_data);
void			feelings(char **line, t_light *light, int line_number, int *flag);
void			more_of_feelings(char **line, t_light *light, int line_number,
									int *flag);

//------------------------------------------------------------------------------------

void			draw_pixel(t_rt *rt_data, t_dot pixel);
int				draw_scene(t_rt *rt_data);
void			ray_tracing(t_rt *rt_data);
t_intersect		find_closest_inter(t_rt *rt_data, t_ray primary_ray);
t_ray			compute_ray(t_camera camera, t_dot pixel);
void			choose_intersection(t_ray primary_ray, t_intersect *tmp_inter);

t_coord_sys	    init_rot_matrix(t_rt *rt_data, int keycode, double angle);
void			rotating_camera(int keycode, t_rt *rt_data);
int				exit_x(t_rt *rt_data, SDL_Event *event);
int				key_down(t_rt *rt_data, SDL_Event *event);
void			event_management(t_rt *rt_data, SDL_Event *event);
t_vector	    choose_normal(t_objects *figure, t_vector inter);
t_vector	    find_normal_to_sphere(t_objects *sphere, t_vector inter);
t_vector	    find_normal_to_cone(t_objects *cone, t_vector inter);
t_vector	    find_normal_to_plane(t_objects *plane, t_vector inter);
t_vector	    find_normal_to_cylinder(t_objects *cyl, t_vector inter);

void		    add_coef(t_channel *coef1, t_channel coef2, float coef);
t_channel	    find_lamp_coef(t_rt *rt_data, t_light *current_lamp, t_intersect closest_inter, t_ray r);
t_ray		    find_light_ray(t_vector origin, t_vector end);
uint32_t	    find_color(t_rt *rt_data, t_intersect closest_inter, t_ray r);

int			    is_shadows_here(t_ray light_ray, t_vector normal, t_ray r);
int			    is_figure_first_inter_by_light(t_rt *rt_data, t_ray light_ray, t_intersect closest_inter);
float		    *find_cos_angle(t_ray light_ray, t_intersect closest_inter, t_vector normal, t_ray r);
uint32_t	    find_color_hex(t_channel light_coef, t_intersect closest_inter);
uint32_t	    find_color_channel(float fig_color_channel, float light_color_channel, int step);

void		    set_pixel(SDL_Surface *surface, int x, int y, uint32_t color);

/* find_intersection directory */
void			sphere_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_sphere_discriminant(t_ray r, t_objects *fig, float coefficient[3]);
int				find_the_root(float coefficient[3], float discriminant, float t[2]);

void			cyl_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_cyl_discriminant(t_ray r, float radius, float *coefficient);

void	        plane_find_closest_intersect(t_ray r, t_intersect *inter);

void	        cone_find_closest_intersect(t_ray r, t_intersect *inter);
float	        find_cone_discriminant(t_ray r, float *coefficient, float coef);
//------------------------------------------------------------------------------------





/*error manager*/
void			error_exit(int error_name,t_rt *rt_data);
void			freesher(t_light *light, t_objects *shapes);
void			error_caster(int line_number, char *s1, char *s2);
/*math_functions*/
t_vector		matrice_mult_vect(t_coord_sys a, t_vector v);
t_coord_sys		count_inverse_matrix(t_coord_sys a);
void			normalize_basis(t_coord_sys *a);
t_coord_sys		matrix_mult_matrix(t_coord_sys a, t_coord_sys b);

t_vector		vect_diff(t_vector v1, t_vector v2);
t_vector		vect_sum(t_vector v1, t_vector v2);
t_vector		vect_mult(t_vector v1, float multiplier);
t_vector		vect_cross_product(t_vector a, t_vector b);
float			vect_scalar_mult(t_vector v1, t_vector v2);
t_vector		normalize_vector(t_vector a);

float			find_square(float a);
float			distance(t_vector v1, t_vector v2);
float			length(t_vector v);








#endif
