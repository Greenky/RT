/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   rt_functions.h                                     :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/07 12:03:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/08/02 11:29:24 by vmazurok         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef RT_FUNCTIONS_H
# define RT_FUNCTIONS_H
# include "rt_structs.h"
# include <fcntl.h>
# include <stdlib.h>
# include <math.h>
# include <unistd.h>
# include <stdio.h>
# include <errno.h>
# include "libft.h"
# include <pthread.h>
# include <time.h>
# include <sys/types.h>
# include <sys/socket.h>
# include <netinet/in.h>
# include <arpa/inet.h>
# include <netdb.h>
# define THREAD_MAX 4
# define PIXEL_SIZE 4
# define FALSE 0
# define TRUE 1
# define DIVISION 0
# define MULTIPLICATION 1
# define SHIFT 0
# define ROTATE 1
# define WIN_SIZE 1000
# define OBJ_NUM 8
# define DISTANCE 1
# define DIRECT_LIGHT_IS_PARSED 15
# define POINT_LIGHT_IS_PARSED 23
# define AMBIENT_LIGHT_IS_PARSED 35
# define SPHERE_IS_PARSED 127
# define CAMERA_IS_PARSED 3
# define CONE_IS_PARSED 1023
# define CYLINDER_IS_PARSED 1023
# define PLANE_IS_PARSED 63
# define ELLIPSOID_IS_PARSED 127
# define TRIANGLE_IS_PARSED 255
# define STEP (1.0 / WIN_SIZE)
# define SHIFT_STEP 0.2
# define LEFT_BOUND (-(WIN_SIZE / 2))
# define TOP_BOUND (-(WIN_SIZE / 2))
# define A 0
# define B 1
# define C 2
# define ANGLE (M_PI * (7) / 180.0)
# define ANGLE_IN_DEGREES(angle) (M_PI * (angle) / 180.0)
# define VEC(a1, a2, a3) (cl_float3){{a1, a2, a3}}
# define W_TITLE "RT by BOMBA_RAKETA"
# define D_BLUE (SDL_Color){33, 150, 243, 0}
# define BLACK (SDL_Color){0, 0, 0, 0}
# define WHITE (SDL_Color){255, 255, 255, 0}
# define GUI_ALIAS_ON_BMP "gui_images/foot_bar_aliasing_on.bmp"
# define GUI_ALIAS_OFF_BMP "gui_images/foot_bar_aliasing_off.bmp"
# define GUI_SEPIA_BMP "gui_images/sepia.bmp"
# define GUI_GREYSCALE_BMP "gui_images/greyscale.bmp"
# define GUI_NEGATIVE_BMP "gui_images/negative.bmp"
# define GUI_PIXEL_BMP "gui_images/pixel.bmp"

int				find_fd(char *file);
void			file_parcing(char *file, t_rt *rt_data);
void			line_reader(t_rt *rt_data, int fd, const t_parce arr[]);
void			parcer_functions(char **str, t_rt *rt_data,
				const t_parce arr[], int fd);
void			correct_plane_normal(t_rt *rt_data);

int				cam_parce(int fd, t_rt *rt_data);
void			camera_data_fill(char **line, t_camera *camera,
								int l_num, int *flag);

int				cone_parce(int fd, t_rt *rt_data);
void			cone_data_fill(char **line, t_objects *cone, int l_num,
								int *flag);
void			more_cone_data_fill(char **line, t_objects *cone, int l_num,
									int *flag);

int				cylinder_parce(int fd, t_rt *rt_data);
void			cylin_data_fill(char **line, t_objects *cyl, int l_num,
								int *flag);
void			more_cylin_data_fill(char **line, t_objects *cyl, int l_num,
									int *flag);

int				sphere_parce(int fd, t_rt *rt_data);
void			sphere_fill(char **line, t_objects *sphere, int l_num,
							int *flag);

int				plane_parce(int fd, t_rt *rt_data);
void			plane_fill(char **line, t_objects *plane, int l_num,
							int *flag);

int				ellipsoid_parce(int fd, t_rt *rt_data);
void			ellipsoid_fill(char **line, t_objects *ellipsoid,
								int line_number, int *flag);
void			more_ellipsoid_fill(char **line,
				t_objects *ellipsoid, int line_number, int *flag);

int				triangle_parce(int fd, t_rt *rt_data);
void			triang_data_fill(char **line, t_objects *cylinder,
								int line_number, int *flag);

void			add_obj_to_list(t_rt *rt_data, t_objects *object);
void			add_light(t_rt *rt_data, t_light *light);

int				begin_with(char *line, char *begin);
char			*trim_from(char *line, int i);

float			drob_finder(char *line, int i, int line_number);
float			str_to_float(char *line, int i, int line_number);

t_channel		parce_color(char *line, int line_number);
float			float_finder(char *line, int *i, int line_number);
cl_float3		parce_vector(char *line, int line_number);

int				light_parce(int fd, t_rt *rt_data);
void			feelings(char **line, t_light *light, int line_number,
						int *flag);
void			more_of_feelings(char **line, t_light *light, int line_number,
									int *flag);

/*
**	draw_scene.c
*/

int				draw_scene(t_rt *rt_data);
void			*draw_strings(void *thread_data_void);
void			set_tread_param(t_rt *scene, t_thread_data *thread_num);
void			draw_pixel_with_aa(t_rt *rt_data, t_dot pixel);
t_channel		get_pixel_color(t_rt *rt_data, t_dot pixel);

/*
**	draw_pixel_filter.c
*/

void			*draw_pixel_strings(void *thread_data_void);
void			draw_pixel_pixel(t_rt *rt_data, t_dot pixel);

/*
**	apply_filter.c
*/

uint32_t		apply_filter(uint32_t color, int filter);

/*
**	run_rt.c
*/

void			run_rt(t_rt *rt_data);
t_ray			compute_ray(t_camera camera, t_dot pixel, int aliasing);
void			load_texture(SDL_Surface **textures, int index,
							const char *path);
void			texture_mapping(t_intersect *closest_inter, t_cl_data cl_data,
							cl_float3 nor, SDL_Surface *texture);
void			get_texture(t_intersect *closest_inter, t_cl_data cl_data);
t_intersect		find_closest_inter(t_cl_data cl_data, t_objects *objects,
									t_ray primary_ray);

/*
**	choose_intersection.c
*/

void			choose_intersection(t_ray primary_ray, t_intersect *tmp_inter);

/*
**	event_management.c
*/

void			event_management(t_rt *rt_data, SDL_Event *event);
int				exit_x(t_rt *rt_data, SDL_Event *event);
int				key_down(t_rt *rt_data, SDL_Event *event);
int				check_sdl_key(int keycode, int type_of_motion);

/*
**	rotating_and_shift_camera.c
*/

void			rotating_camera(int keycode, t_rt *rt_data);
t_coord_sys		init_basis_after_rot(t_coord_sys initial_basis,
										cl_float3 angle_rot);
t_coord_sys		rot_matrix_about_the_axis(float angle, cl_float3 axis);
void			manage_camera_origin(int keycode, t_rt *rt_data);
void			reset_camera_settings(t_rt *rt_data);

/*
**	rotating_objects.c
*/

void			init_obj_basis_after_rot
		(t_coord_sys init_basis_obj, cl_float3 angle_rot, t_objects *obj);
void			check_caps_normals(t_objects *obj);
void			rotating_object(int keycode, t_rt *rt_data);
t_objects		*find_object(t_rt *rt_data);

/*
**	rotating_caps.c
*/

cl_float3		init_cap_axis
		(t_coord_sys new_basis_obj, t_objects *obj, int axis, int cup_num);
void			init_cap_basis_after_rot(t_coord_sys new_basis_obj,
		t_objects *obj, cl_float3 angle_rot, int axis);

/*
**	handle_axis_dimensions_for_ellipsoid.c
*/

float			find_biggest_axis(t_objects *ellipsoid);
void			handle_axis_dimensions(t_objects *ellipsoid);
void			check_axis_dimensions(float *length);
void			manage_ellipsoid_axes(int keycode, t_rt *rt_data);

/*
**	else
*/

cl_float3		choose_normal(t_objects figure, cl_float3 inter);
cl_float3		find_normal_to_sphere(t_objects sphere, cl_float3 inter);
cl_float3		find_normal_to_cone(t_objects cone, cl_float3 inter);
cl_float3		find_normal_to_plane(t_objects plane, cl_float3 inter);
cl_float3		find_normal_to_cylinder(t_objects cyl, cl_float3 inter);
cl_float3		find_normal_to_ellipsoid(t_objects ellipsoid, cl_float3 inter);

t_intersect		find_closest_reflected_inter(t_rt *rt_data,
											t_ray ray, t_objects *this);
void			add_coef(t_channel *coef1, t_channel coef2, float coef);
t_channel		find_lamp_coef(t_rt *rt_data, t_cl_data cl_data,
								t_intersect closest_inter, t_ray r);
t_ray			find_light_ray(cl_float3 origin, t_light *light);
t_channel		find_color(t_rt *rt_data, t_cl_data cl_data,
							t_intersect closest_inter, t_ray r);

int				is_shadows_here(t_ray light_ray, cl_float3 normal, t_ray r);
t_channel		*is_figure_first_inter_by_light(t_rt *rt_data, t_ray light_ray,
				t_intersect closest_inter, t_light *current);
float			*find_cos_angle(t_ray light_ray, t_intersect closest_inter,
								cl_float3 normal, t_ray r);

/*
**	even_more_color_functions.c
*/

t_channel		fig_color_with_light(t_channel light_coef,
									t_intersect closest_inter);
uint32_t		fig_color_with_light_channel(float fig_color,
											float light_color);
t_channel		color_plus_color(t_channel color1, t_channel color2);
uint32_t		channel_color_to_uint(t_channel color);

/*
**	manage_pixel.c
*/

void			set_pixel(SDL_Surface *surface, int x, int y, uint32_t color);

void			sphere_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_sphere_discriminant(t_ray r, t_objects *fig,
										float coefficient[3]);
int				find_the_root(float coefficient[3], float discriminant,
								float t[2]);

void			cyl_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_cyl_discriminant(t_ray r, float radius,
									float *coefficient);
float			limit_cylinder(t_objects cyl, t_ray r, t_intersect *inter,
								float t[2]);

void			plane_find_closest_intersect(t_ray r, t_intersect *inter);

void			cone_find_closest_intersect(t_ray r, t_intersect *inter);
float			find_cone_discriminant(t_ray r, float *coefficient,
										float coef);
float			limit_cone(t_objects con, t_ray r, t_intersect *inter,
							float t[2]);

void			ellipsoid_find_closest_intersect(t_ray r, t_intersect *inter);
t_ray			find_ray_for_imaginary_sphere(t_ray ray, t_objects *ellipsoid);
void			triangle_find_closest_intersect(t_ray r, t_intersect *inter);

/*
**	limitation functions
*/

void			data_validation(t_objects *obj);
void			find_norm_intersections(t_ray r, t_objects obj, float t[2],
								float cap_norm_inter[2][2]);
int				handle_caps_overlap(float cap_norm_inter[2][2], t_objects obj,
								t_intersect *inter);
int				hit_top_cap(float cap_norm_inter[2][2]);
int				hit_bottom_cap(float cap_norm_inter[2][2]);
int				main_object_is_hit(t_intersect *inter, t_ray r, float t[2],
									float cap_norm_inter[2][2]);
int				find_cap_intersection(float cap_norm_inter[2][2],
										t_objects obj, t_intersect *inter);

/*
**	error manager
*/

void			error_exit(int error_name, t_rt *rt_data);
void			freesher(t_light *light, t_objects *shapes);
void			error_caster(int line_number, char *s1, char *s2);
/*
**	math_functions
*/
cl_float3		matrix_mult_vect(t_coord_sys a, cl_float3 v);
t_coord_sys		matrix_mult_matrix(t_coord_sys a, t_coord_sys b);
t_coord_sys		count_inverse_matrix(t_coord_sys a);
void			create_coord_system(t_coord_sys *basis, t_coord_sys *init_basis,
								cl_float3 *angle_rot);

cl_float3		vect_diff(cl_float3 v1, cl_float3 v2);
cl_float3		vect_sum(cl_float3 v1, cl_float3 v2);
cl_float3		vect_mult_scalar(cl_float3 v1, float multiplier);
cl_float3		vect_cross_product(cl_float3 a, cl_float3 b);
float			vect_scalar_mult(cl_float3 v1, cl_float3 v2);
cl_float3		normalize_vector(cl_float3 a);
cl_float3		scale_vector(cl_float3 v, int flag, cl_float3 scale_coef);

float			find_square(float a);
float			distance(cl_float3 v1, cl_float3 v2);
float			length(cl_float3 v);

t_channel		int_to_channels(int col);

void			init_bar_positions(t_rt	*rt_data);
void			init_gui_bmps(t_rt	*rt_data);
void			init_foot_gui_bmps(t_rt *rt_data);

void			change_sphere(t_objects *object, int arrow);
void			change_cylinder(t_objects *object, int arrow);
void			change_cone(t_objects *object, int arrow);
void			change_object(t_objects *object, int arrow);

int				check_arrow_type(SDL_Event *event);
void			gui_interaction_event(t_rt *rt_data, SDL_Event *event);
int				check_foot_press_type(SDL_Event *event);

void			foot_panel_interaction_event(t_rt *rt_data, SDL_Event *event);
void			filter_panel_interaction_event(t_rt *rt_data,
												SDL_Event *event);

void			create_gui(t_rt *rt_data, SDL_Event *event, int flag);
int				check_if_in_gui(t_rt *rt_data, SDL_Event *event);
int				mouse_click_event(t_rt *rt_data, SDL_Event *event);

void			cone_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag,
									t_objects *sphere);
void			cylinder_control_bars_show(t_rt *rt_data, SDL_Rect pos,
										int flag, t_objects *sphere);
void			sphere_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag,
									t_objects *sphere);
void			arrows_active_unactive(t_rt *rt_data, SDL_Rect pos,
									float *min_max, float value);

char			*ftoa(float f, int tochnost);
void			blit_surface_data(t_rt *rt_data, float fdata, SDL_Rect *pos);

void			draw_sphere_info(t_rt *rt_data, t_objects *object);
void			draw_cylinder_info(t_rt *rt_data, t_objects *object);
void			draw_cone_info(t_rt *rt_data, t_objects *object);
void			draw_ellipsoid_info(t_rt *rt_data, t_objects *object);
void			draw_object_info(t_rt *rt_data, int i);

void			draw_clicked_info(t_rt *rt_data);
void			draw_filter_bar(t_rt *rt_data);
void			draw_foot_info(t_rt *rt_data);
void			draw_bar(t_rt *rt_data);
void			draw_gui(t_rt *rt_data);

void			make_screenshot(t_rt *rt_data);
void			swap_cartoon(t_intersect closest_inter, t_rt *rt_data, int i);
void			init_arrays(t_rt *rt_data);

uint32_t		rgb_to_int(t_channel rgb);
int				perlin_noise_disruption(int j, int i);
int				plasma_disruption(int j, int i);
int				check_mate_disruption(int j, int i);
void			parce_limited(char **line, t_objects *obj, int line_number,
							int *flag);

void			*receive_data(int fd, void *dest, size_t size);
void			send_data(int fd, void *src, size_t size);
void			init_server(t_rt *rt_data, char *file);
void			client_event_management(t_rt *rt_data, SDL_Event *event);
#endif
