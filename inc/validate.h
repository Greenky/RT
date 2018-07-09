/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   validate.h                                         :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: dadavyde <dadavyde@student.unit.ua>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/06/15 16:54:00 by dadavyde          #+#    #+#             */
/*   Updated: 2018/06/17 13:16:14 by dadavyde         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef VALIDATE_H
# define VALIDATE_H

int			read_file(t_scene_data *scene, int fd);
void		init_figures(int fd, char **line, t_list **figures);
void		init_lights(int fd, char *line, t_list **lights);

int			check_argument(int fd);
char		*is_scene(int fd);

int			check_camera(int fd, char **line, t_scene_data *scene);
int			check_existence_word(int fd, char **line, char *word);
int			check_origin(int fd, char **line, t_vector *v);
int			check_vector(char *s, t_vector *v);
int			check_basis(int fd, char **line, t_coord_sys *basis);

int			check_figure(int fd, char **line, t_figure *f, int fig_num);
int			check_type_fig(int fd, char **line, int *type);
int			check_radius(int fd, char **line, float *radius_or_cone_coef,
			int type);
int			check_bling_phong(int fd, char **line, int *bling_phong);
void		init_figure_functions(t_figure *fig, int name);

int			check_light(int fd, char **line, t_light *lamp, int lamp_num);
int			check_brightness(int fd, char **line, float *brightness);
int			check_type_light(int fd, char **line, int *type);
int			check_color(int fd, char **line, t_channel *color);

void		check_basis_for_orthogonal(t_coord_sys *a);
t_vector	make_orthogonal_from_vector(t_vector a, t_vector b);
void		init_standart_coord_sys(t_coord_sys *a);
int			is_null_vec(t_vector a);
t_vector	cross_product(t_vector a, t_vector b);

#endif
