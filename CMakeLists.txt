cmake_minimum_required(VERSION 3.9)
project(RT_Clion C)

set(CMAKE_C_STANDARD 90)

execute_process(COMMAND make -C ../libft)

set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra -Werror")
# -O3 -flto=thin -Ofast -march=native -mtune=native")

set(SOURCE_FILES  src/main.c src/draw_scene.c src/manage_pixel.c
src/find_intersection/sphere_find_closest_intersect.c
src/math_functions/actions_on_vectors.c
src/find_pixel_color.c src/find_normal_to_figure.c
src/math_functions/algebraic_operations.c
src/find_intersection/cyl_find_closest_intersect.c
src/find_intersection/plane_find_closest_intersect.c
src/event_management.c src/run_rtv1.c
src/math_functions/actions_on_matrix.c
src/find_intersection/cone_find_closest_intersect.c
src/validate/read_file.c src/validate/check_argument.c
src/validate/check_camera.c src/validate/check_figures.c
src/validate/check_lights.c src/some_find_color_func.c
src/validate/check_basis)

set(HEADERS inc/structs.h inc/rtv1.h inc/validate.h inc/find_intersection.h
inc/math_functions.h)

include_directories(inc) # headers
include_directories(libft)

#include_directories(libft/includes) # lib header directory
link_directories(libft) # library directories

find_library(SDL SDL2)
include_directories(frameworks/SDL2.framework/Headers)
add_executable(rt ${SOURCE_FILES} ${HEADERS})

set_target_properties(rt PROPERTIES
        RUNTIME_OUTPUT_DIRECTORY_DEBUG ${CMAKE_HOME_DIRECTORY})

# linkage
target_link_libraries(rt -L libft -lft ${SDL})
