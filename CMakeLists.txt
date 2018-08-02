cmake_minimum_required(VERSION 3.9)
project(RT)

set(CMAKE_C_STANDARD 90)

execute_process(COMMAND make -C ../libft)
set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror -O3 -flto=thin -Ofast -march=native -mtune=native")

set(SOURCE_FILES
		source/main.c
		source/find_fd.c
		source/error_manager.c
		source/draw_scene/draw_scene.c
		source/find_normal_to_figure.c
		source/run_rt.c
		source/figures_normals.c

		source/parcing_function/file_parcing.c
		source/parcing_function/plane_parcing.c
		source/parcing_function/sphere_parcing.c
		source/parcing_function/cone_parcing.c
		source/parcing_function/cylinder_parcing.c
		source/parcing_function/ellipsoid_parcing.c
		source/parcing_function/cam_parcing.c
		source/parcing_function/add_object_and_light.c
		source/parcing_function/parce_peripherals.c
		source/parcing_function/parce_peripherals_v2.c
		source/parcing_function/light_parcing.c
		source/parcing_function/list_to_objects.c
		source/parcing_function/parce_limited.c

		source/math_functions/actions_on_matrix.c
		source/math_functions/actions_on_vectors.c
		source/math_functions/actions_on_vectors2.c
		source/math_functions/algebraic_operations.c

		source/find_intersection/cone_find_closest_intersect.c
		source/find_intersection/cyl_find_closest_intersect.c
		source/find_intersection/cyl_find_limited.c
		source/find_intersection/plane_find_closest_intersect.c
		source/find_intersection/sphere_find_closest_intersect.c
		source/find_intersection/ellipsoid_find_closest_intersect.c

		source/event_management/event_management.c
		source/event_management/rotating_and_shift_camera.c 
		source/event_management/handle_axis_dimensions_for_ellipsoid.c

		source/gui/gui_object_change.c
		source/gui/gui_check_buttons.c
		source/gui/gui_control_bars_show.c
		source/gui/create_gui.c
		source/gui/gui_draw_objects_info.c
		source/gui/gui_draw_objects_info_2.c
		source/gui/gui_init_bmp.c
		source/gui/gui_utils.c
		source/gui/gui.c

		source/color_functions/perlin_noise.c
		source/color_functions/other_color_disruptions.c
		source/color_functions/find_pixel_color.c
		source/color_functions/manage_pixel.c
		source/color_functions/some_find_color_func.c
		source/color_functions/find_everything.c
		source/color_functions/texture_mapping.c
		source/network_handling.c
		source/color_functions/even_more_color_functions.c
		source/find_intersection/choose_intersection.c
		source/draw_scene/apply_filter.c
		source/draw_scene/draw_pixel_filter.c
		source/event_management/rotating_objects.c
		source/find_intersection/triangle_find_closest_intersect.c
		source/parcing_function/triangle_parce.c source/event_management/rotating_caps.c)
# LIBA for Windows --------------------------------------
#		libft/atoif.c
#		libft/author
#		libft/ft_arraycpy.c
#		libft/ft_atoi.c
#		libft/ft_bzero.c
#		libft/ft_del_all_c.c
#		libft/ft_find_after_c.c
#		libft/ft_find_all_c.c
#		libft/ft_find_c.c
#		libft/ft_isalnum.c
#		libft/ft_isalpha.c
#		libft/ft_isascii.c
#		libft/ft_isdigit.c
#		libft/ft_isnumber.c
#		libft/ft_isprint.c
#		libft/ft_itoa.c
#		libft/ft_lstadd.c
#		libft/ft_lstdel.c
#		libft/ft_lstdelone.c
#		libft/ft_lstiter.c
#		libft/ft_lstmap.c
#		libft/ft_lstnew.c
#		libft/ft_memalloc.c
#		libft/ft_memccpy.c
#		libft/ft_memchr.c
#		libft/ft_memcmp.c
#		libft/ft_memcpy.c
#		libft/ft_memdel.c
#		libft/ft_memmove.c
#		libft/ft_memset.c
#		libft/ft_put_carray.c
#		libft/ft_put_iarray.c
#		libft/ft_putchar.c
#		libft/ft_putchar_fd.c
#		libft/ft_putendl.c
#		libft/ft_putendl_fd.c
#		libft/ft_putnbr.c
#		libft/ft_putnbr_fd.c
#		libft/ft_putstr.c
#		libft/ft_putstr_fd.c
#		libft/ft_str_cpy_to_int_arr.c
#		libft/ft_strcat.c
#		libft/ft_strchr.c
#		libft/ft_strclr.c
#		libft/ft_strcmp.c
#		libft/ft_strcpy.c
#		libft/ft_strdel.c
#		libft/ft_strdup.c
#		libft/ft_strequ.c
#		libft/ft_striter.c
#		libft/ft_striteri.c
#		libft/ft_strjoin.c
#		libft/ft_strlcat.c
#		libft/ft_strlen.c
#		libft/ft_strmap.c
#		libft/ft_strmapi.c
#		libft/ft_strncat.c
#		libft/ft_strncmp.c
#		libft/ft_strncpy.c
#		libft/ft_strnequ.c
#		libft/ft_strnew.c
#		libft/ft_strnstr.c
#		libft/ft_strrchr.c
#		libft/ft_strsplit.c
#		libft/ft_strstr.c
#		libft/ft_strsub.c
#		libft/ft_strtrim.c
#		libft/ft_tolower.c
#		libft/ft_toupper.c
#		libft/get_next_line.c)
		#kernel.c)

#-------------------------------------------------------------

set(HEADERS includes/rt_structs.h includes/rt_functions.h)

include_directories(includes) # headers
include_directories(libft)

link_directories(libft) # library directories

find_library(SDL SDL2)
find_library(SDL_ttf SDL2_ttf)
find_library(SDL_image SDL2_image)

find_package(OpenCL REQUIRED) # OpenCL package
# MAC OS -------------
include_directories(frameworks/SDL2.framework/Versions/A/Headers)
include_directories(frameworks/SDL2_image.framework/Versions/A/Headers)
include_directories(frameworks/SDL2_ttf.framework/Versions/A/Headers)
#--------------------

include_directories(${OpenCL_INCLUDE_DIRS})
link_directories(${OpenCL_LIBRARY})

# Windows -----------
#include_directories(frameworks/SDL_Windows/include/SDL2)
#--------------------
add_executable(RT ${SOURCE_FILES} ${HEADERS})

set_target_properties(RT PROPERTIES
		RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY})

target_link_libraries(RT ${SDL} ${SDL_image} ${SDL_ttf} ${OpenCL_LIBRARY} -lft pthread)