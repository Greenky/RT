#******************************************************************************#
#                                                                              #
#                                                         :::      ::::::::    #
#    Makefile                                           :+:      :+:    :+:    #
#                                                     +:+ +:+         +:+      #
#    By: vmazurok <marvin@42.fr>                    +#+  +:+       +#+         #
#                                                 +#+#+#+#+#+   +#+            #
#    Created: 2018/03/30 21:52:55 by vmazurok          #+#    #+#              #
#    Updated: 2018/03/30 21:52:58 by vmazurok         ###   ########.fr        #
#                                                                              #
#******************************************************************************#
# -Wall -Wextra -Werror
CC		=	gcc
CFLAGS	=	-O3 -Wall -Wextra -Werror
GFX		=	-lmlx -framework OpenGL -framework AppKit
NAME	=	RTv1
SRC		=	get_next_line.c \
			main.c \
			ray_tracing.c \
			vector_functions.c \
			vector_functions_v2.c \
			sphere_func.c \
			cone_func.c \
			cylin_func.c \
			plane_func.c \
			parce_peripherals.c \
			parce_peripherals_v2.c \
			light_manipulation.c \
			light_calculation.c \
			file_parcing.c
			
BINS = $(SRC:.c=.o)

all: $(NAME)

$(NAME): $(BINS)
	cd libft ; make ; cd ..
	$(CC) $(CFLAGS) -o $(NAME) $(BINS) $(GFX) libft/libft.a

.c.o:
	$(CC) -c $(CFLAGS) $<

clean:
	cd libft ; make clean ; cd ..
	rm -f $(BINS)

fclean: clean
	cd libft ; make fclean ; cd ..
	rm -f $(NAME)

re: fclean all