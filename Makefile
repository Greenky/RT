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

CC = gcc
C_FLAGS = -c -Wall -Wextra -Werror -O3 -flto=thin -Ofast -march=native -mtune=native
RTV_FLAGS = -F frameworks/ -framework SDL2

SOURCES = src/main.c src/draw_scene.c src/manage_pixel.c\
		src/find_intersection/sphere_find_closest_intersect.c\
        src/math_functions/actions_on_vectors.c\
        src/find_pixel_color.c src/find_normal_to_figure.c\
        src/math_functions/algebraic_operations.c\
        src/find_intersection/cyl_find_closest_intersect.c\
        src/find_intersection/plane_find_closest_intersect.c\
        src/event_management.c src/run_rtv1.c\
        src/math_functions/actions_on_matrix.c\
        src/find_intersection/cone_find_closest_intersect.c\
        src/validate/read_file.c src/validate/check_argument.c\
        src/validate/check_camera.c src/validate/check_figures.c\
        src/validate/check_lights.c src/some_find_color_func.c\
        src/validate/check_basis.c

HEADERS = inc/structs.h inc/rtv1.h inc/validate.h inc/find_intersection.h\
		inc/math_functions.h
INCLUDES = -I libft/
INCLUDES_SDL = -I frameworks/SDL2.framework/Headers/

OBJ = $(addprefix $(OBJDIR), $(notdir $(SOURCES:.c=.o)))
OBJDIR = obj/

LIBFT = libft/libft.a
NAME = RT

all: $(NAME)

$(NAME): $(OBJDIR) $(OBJ) $(LIBFT)
	$(CC)  $(OBJ) $(RTV_FLAGS) -o $@ $(LIBFT)

$(OBJDIR)%.o: src/find_intersection/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: src/math_functions/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: src/%.c $(HEADERS) $(SOURCES) $(LIBFT)
	$(CC)  $(C_FLAGS) $(INCLUDES_SDL) $< -o $@ $(INCLUDES)

$(OBJDIR)%.o: src/validate/%.c $(HEADERS) $(SOURCES) $(LIBFT)
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
	rm -f $(NAME)

re: fclean all
