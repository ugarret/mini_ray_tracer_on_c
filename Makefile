CC =			gcc

FLAGS =			-Werror -Wextra -Wall -g

RM =			rm -rf

DIR_HEADERS =	./includes/

DIR_SRCS =		./srcs/

DIR_OBJS =		./

LIBMLX =		libmlx.dylib

SRC =			my_atof.c \
				my_atoi.c \
				my_strlen.c \
				get_line_from_file.c \
				parser.c \
				main.c \
				my_isdigit.c \
				my_substr.c \
				parcer_set_param_obj.c \
				my_isalpha.c \
				my_skip_space.c \
				my_split.c \
				my_strncmp.c \
				my_list_new.c \
				my_add_object_back.c \
				my_bzero.c \
				my_calloc.c \
				my_memset.c \
				my_matrix.c \
				my_vector_1.c \
				my_vector_2.c \
				my_sphere.c \
				my_plane.c \
				my_triangle.c \
				my_cylinder.c \
				my_square.c \
				my_save_bmp.c \
				my_error.c \
				my_render.c \
				my_work_with_color.c

SRCS =			$(addprefix $(DIR_SRCS), $(SRC))

COMPIL =		$(FLAGS)

OBJS =			$(SRCS:.c=.o)

NAME =			miniRT

.PHONY:			all, clean, fclean, re, bonus

all:			$(NAME)

$(NAME) :		$(OBJS)
				@make -C ./minilibx_mms
				@make -C ./minilibx_opengl
				@cp ./minilibx_mms/libmlx.dylib libmlx.dylib
				@$(CC) $(COMPIL) -I $(DIR_HEADERS) $(LIBMLX) $(OBJS) -o $(NAME)

%.o: %.c
				@gcc $(FLAGS) -I $(DIR_HEADERS) -c $< -o $@


clean:
				$(RM) $(OBJS)

fclean:			clean
				@make clean -C ./minilibx_mms
				@make clean -C ./minilibx_opengl
				$(RM) libmlx.dylib
				$(RM) $(NAME)

re:				fclean all
