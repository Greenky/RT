/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rtv1.h                                             :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/05/20 18:12:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 17:58:59 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RTV1_H
# define RTV1_H

# include "SDL.h"
# include "libft.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <pthread.h>
# include <sys/types.h>
# include "structs.h"
# include "validate.h"
# include "find_intersection.h"
# include "math_functions.h"

# define FALSE 0
# define TRUE 1

# define WIN_WIDTH 1000
# define WIN_HEIGHT 1000
# define DISTANCE 1
# define STEP (1.0 / WIN_WIDTH)
# define LEFT_BOUND (-(WIN_WIDTH / 2))
# define TOP_BOUND (-(WIN_HEIGHT / 2))
# define A 0
# define B 1
# define C 2
# define THREAD_MAX 4
# define ANGLE (M_PI * (5) / 180.0)

# define VEC(a1, a2, a3) (t_vector){a1, a2, a3}

# define W_TITLE "RTv1 by dadavyde"

int			draw_all_scene(t_scene_data *scene);
void		*draw_strings(void *thread_data_void);
void		set_tread_param(t_scene_data *scene, t_thread_data *thread_num);
void		draw_pixel(t_scene_data *scene, t_dot pixel);

void		run_rtv1(t_scene_data *scene);
t_ray		compute_ray(t_cam camera, t_dot pixel);
t_intersect	find_closest_inter(t_scene_data *scene, t_ray primary_ray);

void		set_pixel(SDL_Surface *surface, int x, int y, Uint32 color);

uint32_t	find_color(t_scene_data *scene, t_intersect closest_inter, t_ray r);
void		add_coef(t_channel *coef1, t_channel coef2, float coef);
t_channel	find_lamp_coef(t_scene_data *scene, t_light *current_lamp,
			t_intersect closest_inter, t_ray r);
t_ray		find_light_ray(t_vector origin, t_vector end);

int			is_shadows_here(t_ray light_ray, t_vector normal, t_ray r);
int			is_figure_first_inter_by_light(t_scene_data *scene, t_ray light_ray,
										t_intersect closest_inter);
float		*find_cos_angle(t_ray light_ray, t_intersect closest_inter,
			t_vector normal, t_ray r);
uint32_t	find_color_hex(t_channel light_coef, t_intersect closest_inter);
uint32_t	find_color_channel(float fig_color_channel,
			float light_color_channel, int step);

void		event_management(t_scene_data *scene, SDL_Event *event);
int			exit_x(t_scene_data *scene, SDL_Event *event);
int			key_down(t_scene_data *scene, SDL_Event *event);
void		rotating_camera(int keycode, t_scene_data *scene);
t_coord_sys	init_rot_matrix(int keycode, double angle);

t_vector	find_normal_to_sphere(t_figure *fig, t_vector inter);
t_vector	find_normal_to_cone(t_figure *cone, t_vector inter);
t_vector	find_normal_to_plane(t_figure *plane, t_vector inter);
t_vector	find_normal_to_cylinder(t_figure *cyl, t_vector inter);

#endif
