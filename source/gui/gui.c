/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   gui.c                                              :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: ikachko <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2018/07/19 13:15:46 by ikachko           #+#    #+#             */
/*   Updated: 2018/07/19 13:17:19 by ikachko          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#include "../includes/rt_functions.h"

char*	ftoa(float f, int tochnost)
{
	char	*first_part;
	char	*second_part;
	char	*buffer1;

	buffer1 = ft_itoa((int)f);
	if (f > -1 && f < 0 && (first_part = ft_strjoin("-", buffer1)))
		free(buffer1);
	else
		first_part = buffer1;
	if (f < 0)
		f *= -1;
	f = f - (int)f;
	while (tochnost > 0 && (f *= 10))
		tochnost--;
	second_part = ft_itoa((int)f);
	buffer1 = first_part;
	first_part = ft_strjoin(first_part, ".");
	free(buffer1);
	buffer1 = first_part;
	first_part = ft_strjoin(first_part, second_part);
	free(second_part);
	free(buffer1);
	return (first_part);
}

void		blit_surface_data(t_rt *rt_data, float fdata, SDL_Rect *pos)
{
	char		*str_data;

	str_data = ftoa(fdata, 1);
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.open_sans, str_data, BLACK, WHITE), NULL, rt_data->screen_surface, pos);
	free(str_data);
}

void		arrows_active_unactive(t_rt *rt_data, SDL_Rect pos, float *min_max, float value)
{
	SDL_Rect	left;
	SDL_Rect	right;
	SDL_Rect	text;

	left.x = pos.x - 80;
	left.y = pos.y;
	right.x = pos.x + 50;
	right.y = pos.y;
	text.x = left.x + 35;
	text.y = pos.y + 6;
	SDL_BlitSurface(rt_data->gui.little_text_area, NULL,
					rt_data->screen_surface, &text);
	if (value >= min_max[0])
		SDL_BlitSurface(rt_data->gui.arrow_left_active, NULL,
						rt_data->screen_surface, &left);
	else
		SDL_BlitSurface(rt_data->gui.arrow_left_unactive, NULL,
						rt_data->screen_surface, &left);
	if (value <= min_max[1])
		SDL_BlitSurface(rt_data->gui.arrow_right_active, NULL,
						rt_data->screen_surface, &right);
	else
		SDL_BlitSurface(rt_data->gui.arrow_right_unactive, NULL,
						rt_data->screen_surface, &right);
}

void		sphere_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag, t_objects *sphere)
{
	float		min_max[2];

	min_max[0] = -100;
	min_max[1] = 100;
	if (flag == RADIUS)
	{
		min_max[0] = 1.0;
		min_max[1] = 50.0;
		arrows_active_unactive(rt_data, pos, min_max, sphere->radius);
	}
	else if (flag == POS_X)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.x);
	else if (flag == POS_Y)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.y);
	else if (flag == POS_Z)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.z);
}

void		cylinder_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag, t_objects *sphere)
{
	float		min_max[2];

	min_max[0] = -100;
	min_max[1] = 100;
	if (flag == RADIUS)
	{
		min_max[0] = 1.0;
		min_max[1] = 50.0;
		arrows_active_unactive(rt_data, pos, min_max, sphere->radius);
	}
	else if (flag == POS_X)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.x);
	else if (flag == POS_Y)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.y);
	else if (flag == POS_Z)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.z);
}

void		cone_control_bars_show(t_rt *rt_data, SDL_Rect pos, int flag, t_objects *sphere)
{
	float		min_max[2];

	min_max[0] = -100;
	min_max[1] = 100;
	if (flag == ANGLE_KOEF)
	{
		min_max[0] = 0.2;
		min_max[1] = 3.0;
		arrows_active_unactive(rt_data, pos, min_max, sphere->angle_coef);
	}
	else if (flag == POS_X)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.x);
	else if (flag == POS_Y)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.y);
	else if (flag == POS_Z)
		arrows_active_unactive(rt_data, pos, min_max, sphere->origin.z);
}

void		draw_sphere_info(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;

	pos = (SDL_Rect){50, 35, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Sphere", BLACK, WHITE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){56, 100, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Radius: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 120, 0, 0};
	sphere_control_bars_show(rt_data, pos, RADIUS, object);
	pos = (SDL_Rect){88, 128, 0, 0};
	blit_surface_data(rt_data, object->radius, &pos);
	pos = (SDL_Rect){85, 155, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "X: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 175, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_X, object);
	pos = (SDL_Rect){88, 183, 0, 0};
	blit_surface_data(rt_data, object->origin.x, &pos);
	pos = (SDL_Rect){85, 210, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Y: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 230, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_Y, object);
	pos = (SDL_Rect){88, 238, 0, 0};
	blit_surface_data(rt_data, object->origin.y, &pos);
	pos = (SDL_Rect){85, 265, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Z: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 285, 0, 0};
	sphere_control_bars_show(rt_data, pos, POS_Z, object);
	pos = (SDL_Rect){88, 293, 0, 0};
	blit_surface_data(rt_data, object->origin.z, &pos);
}

void	draw_cylinder_info(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;

	pos = (SDL_Rect){45, 35, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Cylinder", BLACK, WHITE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){56, 100, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Radius: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 120, 0, 0};
	cylinder_control_bars_show(rt_data, pos, RADIUS, object);
	pos = (SDL_Rect){88, 128, 0, 0};
	blit_surface_data(rt_data, object->radius, &pos);
	pos = (SDL_Rect){85, 155, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "X: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 175, 0, 0};
	cylinder_control_bars_show(rt_data, pos, POS_X, object);
	pos = (SDL_Rect){88, 183, 0, 0};
	blit_surface_data(rt_data, object->origin.x, &pos);
	pos = (SDL_Rect){85, 210, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Y: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 230, 0, 0};
	cylinder_control_bars_show(rt_data, pos, POS_Y, object);
	pos = (SDL_Rect){88, 238, 0, 0};
	blit_surface_data(rt_data, object->origin.y, &pos);
	pos = (SDL_Rect){85, 265, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Z: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 285, 0, 0};
	cylinder_control_bars_show(rt_data, pos, POS_Z, object);
	pos = (SDL_Rect){88, 293, 0, 0};
	blit_surface_data(rt_data, object->origin.z, &pos);
}

void	draw_cone_info(t_rt *rt_data, t_objects *object)
{
	SDL_Rect	pos;

	pos = (SDL_Rect){45, 35, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Cone", BLACK, WHITE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){56, 100, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Angle: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 120, 0, 0};
	cone_control_bars_show(rt_data, pos, ANGLE_KOEF, object);
	pos = (SDL_Rect){88, 128, 0, 0};
	blit_surface_data(rt_data, object->angle_coef, &pos);
	pos = (SDL_Rect){85, 155, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "X: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 175, 0, 0};
	cone_control_bars_show(rt_data, pos, POS_X, object);
	pos = (SDL_Rect){88, 183, 0, 0};
	blit_surface_data(rt_data, object->origin.x, &pos);
	pos = (SDL_Rect){85, 210, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Y: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 230, 0, 0};
	cone_control_bars_show(rt_data, pos, POS_Y, object);
	pos = (SDL_Rect){88, 238, 0, 0};
	blit_surface_data(rt_data, object->origin.y, &pos);
	pos = (SDL_Rect){85, 265, 0, 0};
	SDL_BlitSurface(TTF_RenderText_Shaded(rt_data->gui.chunk_font, "Z: ", BLACK, DEEP_BLUE), NULL, rt_data->screen_surface, &pos);
	pos = (SDL_Rect){88, 285, 0, 0};
	cone_control_bars_show(rt_data, pos, POS_Z, object);
	pos = (SDL_Rect){88, 293, 0, 0};
	blit_surface_data(rt_data, object->origin.z, &pos);
}

void	draw_object_info(t_rt *rt_data, int i)
{
	if (rt_data->objects_arr[i].type == SPHERE)
		draw_sphere_info(rt_data, &rt_data->objects_arr[i]);
	else if (rt_data->objects_arr[i].type == CYLINDER)
		draw_cylinder_info(rt_data, &rt_data->objects_arr[i]);
	else if (rt_data->objects_arr[i].type == CONE)
		draw_cone_info(rt_data, &rt_data->objects_arr[i]);
}

void		sdl_error(char *str)
{
	ft_putstr(str);
	ft_putendl(SDL_GetError());
	exit(1);
}

void		init_gui_bmps(t_rt *rt_data)
{
	if (!(rt_data->gui.bar = SDL_LoadBMP("gui_images/info_bar.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.arrow_left_active = SDL_LoadBMP("gui_images/arrow_left_active.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.arrow_right_active = SDL_LoadBMP("gui_images/arrow_right_active.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.arrow_left_unactive = SDL_LoadBMP("gui_images/arrow_left_unactive.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.arrow_right_unactive = SDL_LoadBMP("gui_images/arrow_right_unactive.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.little_text_area = SDL_LoadBMP("gui_images/little_text_area.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.big_text_area = SDL_LoadBMP("gui_images/big_text_area.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.checked = SDL_LoadBMP("gui_images/checked.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.unchecked = SDL_LoadBMP("gui_images/unchecked.bmp")))
		sdl_error("SDL_LoadBMP failed: ");
}

void	init_foot_gui_bmps(t_rt *rt_data)
{
	if (!(rt_data->gui.aliasing_on_foot = SDL_LoadBMP(GUI_ALIAS_ON_BMP)))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.aliasing_off_foot = SDL_LoadBMP(GUI_ALIAS_OFF_BMP)))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.sepia = SDL_LoadBMP(GUI_SEPIA_BMP)))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.greyscale = SDL_LoadBMP(GUI_GREYSCALE_BMP)))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.negative = SDL_LoadBMP(GUI_NEGATIVE_BMP)))
		sdl_error("SDL_LoadBMP failed: ");
	if (!(rt_data->gui.pixel = SDL_LoadBMP(GUI_PIXEL_BMP)))
		sdl_error("SDL_LoadBMP failed: ");
}

void		init_bar_positions(t_rt	*rt_data)
{
    rt_data->take_screenshot = 0;
	rt_data->gui.bar_pos = (SDL_Rect){0, 0, 0, 0};
	rt_data->gui.big_text_area_pos = (SDL_Rect){25, 25, 0, 0};
}

void		draw_clicked_info(t_rt *rt_data)
{
	int	i;

	i = -1;
	while (++i < rt_data->cl_data.num_of_objects)
	{
		if (rt_data->objects_arr[i].is_cartoon)
		{
			draw_bar(rt_data);
			draw_object_info(rt_data, i);
		}
	}
}

void		draw_filter_bar(t_rt *rt_data)
{
	rt_data->gui.pos = (SDL_Rect){0, SCR_SIZE - 430, 0, 0};
	printf("qq\n");
	if (rt_data->filter == NONE)
		rt_data->filter = GREYSCALE;
	if (rt_data->filter == SEPIA)
		SDL_BlitSurface(rt_data->gui.sepia, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
	else if (rt_data->filter == GREYSCALE)
		SDL_BlitSurface(rt_data->gui.greyscale, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
	else if (rt_data->filter == NEGATIVE)
		SDL_BlitSurface(rt_data->gui.negative, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
	else if (rt_data->filter == PIXEL)
		SDL_BlitSurface(rt_data->gui.pixel, NULL,
			rt_data->screen_surface, &rt_data->gui.pos);
}

void		draw_foot_info(t_rt *rt_data)
{
	rt_data->gui.pos = (SDL_Rect){0, SCR_SIZE - 100, 0, 0};
	if (rt_data->aliasing)
		SDL_BlitSurface(rt_data->gui.aliasing_on_foot, NULL,
						rt_data->screen_surface, &rt_data->gui.pos);
	else
		SDL_BlitSurface(rt_data->gui.aliasing_off_foot, NULL,
						rt_data->screen_surface, &rt_data->gui.pos);
	if (rt_data->gui.filter_gui)
		draw_filter_bar(rt_data);
}

void		draw_bar(t_rt *rt_data)
{
	SDL_BlitSurface(rt_data->gui.bar, NULL, rt_data->screen_surface, &rt_data->gui.bar_pos);
	SDL_BlitSurface(rt_data->gui.big_text_area, NULL, rt_data->screen_surface, &rt_data->gui.big_text_area_pos);
}

void		draw_gui(t_rt *rt_data)
{
	TTF_Init();
	rt_data->gui.chunk_font = TTF_OpenFont("fonts/OpenSans-Bold.ttf", 20);
	rt_data->gui.open_sans = TTF_OpenFont("fonts/OpenSans-Regular.ttf", 15);
	draw_clicked_info(rt_data);
	draw_foot_info(rt_data);
	TTF_Quit();
}