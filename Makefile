# **************************************************************************** #
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: dadavyde <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/06/17 14:33:17 by dadavyde          #+#    #+#              #
#    Updated: 2018/06/17 14:33:21 by dadavyde         ###   ########.fr        #
#                                                                              #
# **************************************************************************** #

CC              =   gcc
C_FLAGS         =   -c -Wall -Wextra -Werror -O3 -flto=thin -Ofast -march=native -mtune=native
RTV_FLAGS       =   -F frameworks/ -framework SDL2

SOURCES         =   source/main.c\
                    source/parcing_function/file_parcing.c\
					source/parcing_function/find_fd.c\
					source/parcing_function/plane_parcing.c\
					source/parcing_function/sphere_parcing.c\
					source/parcing_function/cone_parcing.c\
					source/parcing_function/cylinder_parcing.c\
					source/parcing_function/cam_parcing.c\
					source/ray_traycing_functions/error_manager.c\
					source/parcing_function/add_shape_and_light.c\
					source/parcing_function/parce_peripherals.c\
					source/parcing_function/parce_peripherals_v2.c\
					source/parcing_function/light_parcing.c\
					source/math_functions/actions_on_matrix.c\
					source/math_functions/actions_on_vectors.c\
					source/math_functions/algebraic_operations.c\
					source/ray_traycing_functions/draw_scene.c\
					source/event_management/event_management.c\
					source/find_normal/find_normal_for_other_figure.c\
					source/color_functions/find_pixel_color.c\
					source/ray_traycing_functions/manage_pixel.c\
					source/ray_traycing_functions/ray_tracing.c\
					source/color_functions/some_find_color_func.c\
					source/find_intersection/cone_find_closest_intersect.c\
					source/find_intersection/cyl_find_closest_intersect.c\
					source/find_intersection/plane_find_closest_intersect.c\
					source/find_intersection/sphere_find_closest_intersect.c\
					source/find_intersection/ellipsoid_find_closest_intersec.c\
					source/event_management/handle_axis_dimensions_for_ellipsoid.c\
					source/parcing_function/ellipsoid_parcing.c \
					source/event_management/rotating_and_shift_camera.c\
					source/find_normal/find_normal_for_basic_figure.c
        

HEADERS         =   includes/rt_functions.h includes/rt_structs.h

INCLUDES        =   -I libft/

INCLUDES_SDL    =   -I frameworks/SDL2.framework/Headers/

OBJ             =   $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))

OBJDIR          =   obj/

LIBFT           =   libft/libft.a

NAME            =   RT

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFT)
	$(CC)  $(OBJ) $(RTV_FLAGS) -o $@ $(LIBFT)

$(OBJDIR)%.o: source/find_intersection/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: source/math_functions/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: source/parcing_function/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: source/ray_traycing_functions/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: source/event_management/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: source/find_normal/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)


$(OBJDIR)%.o: source/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: source/color_functions/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)


$(LIBFT):
	make -C libft

$(OBJDIR): $(HEADERS) $(LIBFT)
	mkdir -p $(OBJDIR)

clean:
	rm -f $(OBJ)
	make clean -C libft
	rm -rf $(OBJDIR)

fclean: clean
	echo $(OBJ)
	make fclean -C libft
	rm -f $(NAME)

re: fclean all
