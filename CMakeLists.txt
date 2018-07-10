cmake_minimum_required(VERSION 3.9)
project(RT_Clion C)

set(CMAKE_C_STANDARD 90)

execute_process(COMMAND make -C ../libft)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
# -O3 -flto=thin -Ofast -march=native -mtune=native")

set(SOURCE_FILES  source/main.c
        source/parcing_function/file_parcing.c
        source/find_fd.c
        source/parcing_function/shape_parcing.c
        source/parcing_function/plane_parcing.c
        source/parcing_function/sphere_parcing.c
        source/parcing_function/cone_parcing.c
        source/parcing_function/cylinder_parcing.c
        source/parcing_function/cam_parcing.c
        source/error_manager.c
        source/parcing_function/add_shape_and_light.c
        source/parcing_function/parce_peripherals.c
        source/parcing_function/parce_peripherals_v2.c
        source/parcing_function/light_parcing.c
        source/math_functions/actions_on_matrix.c
        source/math_functions/actions_on_vectors.c
        source/math_functions/algebraic_operations.c
        source/draw_scene.c
        source/event_management.c
        source/find_normal_to_figure.c
        source/find_pixel_color.c
        source/manage_pixel.c
        source/run_rtv1.c
        source/some_find_color_func.c
        source/find_intersection/cone_find_closest_intersect.c
        source/find_intersection/cyl_find_closest_intersect.c
        source/find_intersection/plane_find_closest_intersect.c
        source/find_intersection/sphere_find_closest_intersect.c)

set(HEADERS includes/rt_structs.h includes/rt_functions.h)

include_directories(includes) # headers
include_directories(libft)

#include_directories(libft/includes) # lib header directory
link_directories(libft) # library directories

find_library(SDL SDL2)
include_directories(frameworks/SDL2.framework/Headers)
add_executable(rt ${SOURCE_FILES} ${HEADERS})

set_target_properties(rt PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY})

# linkage
target_link_libraries(rt -lft ${SDL})
