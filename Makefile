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


WWW             =   -Wall -Wextra -Werror # НЕ ЗАБУДЬ ПОВЕРНУТИ МУДІЛА


C_FLAGS         =   -c -O3 -flto=thin -Ofast -march=native -mtune=native -Wall -Wextra -Werror
RTV_FLAGS       =   -F frameworks -framework SDL2 -framework SDL2_ttf -framework SDL2_image -framework OpenCL

SOURCES         =   source/draw_scene.c \
                    source/error_manager.c \
                    source/event_management.c \
                    source/find_fd.c \
                    source/find_normal_to_figure.c \
                    source/find_pixel_color.c \
                    source/main.c \
                    source/manage_pixel.c \
                    source/run_rtv1.c \
                    source/some_find_color_func.c \
                    source/parcing_function/add_shape_and_light.c \
                    source/parcing_function/cam_parcing.c \
                    source/parcing_function/cone_parcing.c \
                    source/parcing_function/cylinder_parcing.c \
                    source/parcing_function/file_parcing.c \
                    source/parcing_function/light_parcing.c \
                    source/parcing_function/parce_peripherals.c \
                    source/parcing_function/parce_peripherals_v2.c \
                    source/parcing_function/plane_parcing.c \
                    source/parcing_function/sphere_parcing.c \
                    source/math_functions/actions_on_matrix.c \
                    source/math_functions/actions_on_vectors.c \
                    source/math_functions/actions_on_vectors2.c \
                    source/math_functions/algebraic_operations.c \
                    source/find_intersection/cone_find_closest_intersect.c \
                    source/find_intersection/cyl_find_closest_intersect.c \
                    source/find_intersection/plane_find_closest_intersect.c \
                    source/find_intersection/sphere_find_closest_intersect.c \
                    source/gui/gui_object_change.c      \
                    source/gui/gui_check_buttons.c      \
                    source/gui/create_gui.c             \
                    source/gui/gui_control_bars_show.c  \
                    source/gui/gui_draw_objects_info.c  \
                    source/gui/gui_draw_objects_info_2.c \
                    source/gui/gui_init_bmp.c           \
                    source/gui/gui_utils.c              \
                    source/gui/gui.c

        
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

OBJDIR          =   objects/

LIBFT           =   libft/libft.a

NAME            =   RT

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFT)
	@$(CC)  $(OBJ) $(RTV_FLAGS) -o $@ $(LIBFT)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/find_intersection/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/math_functions/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/parcing_function/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_GREEN)[done]$(C_NONE)\n" $@

$(OBJDIR)%.o: source/gui/%.c $(HEADERS) $(LIBFT)
	@$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_GREEN)[done]$(C_NONE)\n" $@

$(LIBFT):
	@make -C libft

$(OBJDIR): $(HEADERS) $(LIBFT)
	@mkdir -p $(OBJDIR)

clean:
	@rm -f $(OBJ)
	@make clean -C libft
	@rm -rf $(OBJDIR)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_RED)[done]$(C_NONE)\n" $@

fclean: clean
	@make fclean -C libft
	@rm -f $(NAME)
	@printf "$(C_MAGENTA)RT:   $(C_NONE) %-39s$(C_RED)[done]$(C_NONE)\n" $@

re: fclean all
