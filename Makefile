# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/17 14:33:17 by dadavyde          #+#    #+#              #
#    Updated: 2018/08/02 11:11:00 by vmazurok         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              =   gcc

C_FLAGS         =   -c -O3 -flto=thin -Ofast -march=native -mtune=native

RTV_FLAGS       =   -F frameworks -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework OpenCL

SERVER_SRC		=	source/main.c

CLIENT_SRC		=	source/client_main.c

SOURCES         =   source/error_manager.c \
                    source/run_rt.c \
                    source/network_handling.c \
                    source/event_management/event_management.c \
                    source/event_management/handle_axis_dimensions_for_ellipsoid.c \
                    source/event_management/rotating_and_shift_camera.c \
                    source/event_management/rotating_objects.c \
                    source/event_management/rotating_caps.c \
                    source/find_fd.c \
                    source/figures_normals.c \
                    source/find_normal_to_figure.c \
                    source/draw_scene/apply_filter.c \
                    source/draw_scene/draw_pixel_filter.c \
                    source/draw_scene/draw_scene.c \
                    source/parcing_function/add_object_and_light.c \
                    source/parcing_function/cam_parcing.c \
                    source/parcing_function/cone_parcing.c \
                    source/parcing_function/cylinder_parcing.c \
                    source/parcing_function/file_parcing.c \
                    source/parcing_function/light_parcing.c \
                    source/parcing_function/parce_peripherals.c \
                    source/parcing_function/parce_peripherals_v2.c \
                    source/parcing_function/plane_parcing.c     \
                    source/parcing_function/sphere_parcing.c    \
                    source/parcing_function/list_to_objects.c   \
                    source/parcing_function/ellipsoid_parcing.c \
                    source/parcing_function/parce_limited.c \
                    source/parcing_function/triangle_parce.c \
                    source/math_functions/actions_on_matrix.c \
                    source/math_functions/actions_on_vectors.c \
                    source/math_functions/actions_on_vectors2.c \
                    source/math_functions/algebraic_operations.c \
                    source/find_intersection/cone_find_closest_intersect.c \
                    source/find_intersection/cyl_find_closest_intersect.c \
                    source/find_intersection/cyl_find_limited.c \
                    source/find_intersection/plane_find_closest_intersect.c \
                    source/find_intersection/sphere_find_closest_intersect.c \
                    source/find_intersection/ellipsoid_find_closest_intersect.c \
                    source/find_intersection/choose_intersection.c \
                    source/find_intersection/triangle_find_closest_intersect.c \
                    source/gui/gui_object_change.c      \
                    source/gui/gui_check_buttons.c      \
                    source/gui/create_gui.c             \
                    source/gui/gui_control_bars_show.c  \
                    source/gui/gui_draw_objects_info.c  \
                    source/gui/gui_draw_objects_info_2.c \
                    source/gui/gui_init_bmp.c           \
                    source/gui/gui_utils.c              \
                    source/gui/gui.c                    \
                    source/color_functions/perlin_noise.c \
                    source/color_functions/other_color_disruptions.c \
                    source/color_functions/find_pixel_color.c       \
                    source/color_functions/find_everything.c        \
                    source/color_functions/some_find_color_func.c   \
                    source/color_functions/manage_pixel.c   \
                    source/color_functions/even_more_color_functions.c \
                    source/color_functions/texture_mapping.c

        
C_RED = \033[31m
C_GREEN = \033[32m
C_MAGENTA = \033[35m
C_NONE = \033[0m

HEADERS         =   includes/rt_functions.h includes/rt_structs.h

INCLUDES        =   -I libft/

SDL    =   -I frameworks/SDL2.framework/Version/A/Headers/
SDL_TTF = -I frameworks/SDL2_ttf.framework/Version/A/Headers/
SDL_IMAGE = -I frameworks/SDL2_image.framework/Version/A/Headers/

INCLUDES_SDL = $(SDL) $(SDL_TTF) $(SDL_IMAGE)

OBJ             =   $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))

S_OBJ           =   $(addprefix $(OBJDIR), $(notdir $(SERVER_SRC:.c=.o)))

C_OBJ           =   $(addprefix $(OBJDIR), $(notdir $(CLIENT_SRC:.c=.o)))

OBJDIR          =   objects/

LIBFT           =   libft/libft.a

NAME            =   RT

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFT) $(S_OBJ) $(C_OBJ)
	@$(CC)  $(OBJ) $(S_OBJ) $(RTV_FLAGS) -o $@ $(LIBFT)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@
	@$(CC)  $(OBJ) $(C_OBJ) $(RTV_FLAGS) -o RT_CLIENT $(LIBFT)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" RT_CLIENT

$(OBJDIR)%.o: source/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/event_management/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/find_intersection/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/math_functions/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/parcing_function/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/gui/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/color_functions/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/draw_scene/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_GREEN)[done]$(C_NONE)\n" $@

$(LIBFT):
	@make -C libft

$(OBJDIR): $(HEADERS) $(LIBFT)
	@mkdir -p $(OBJDIR)

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@rm -rf $(OBJDIR)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@rm -f RT_CLIENT
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-50s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all
