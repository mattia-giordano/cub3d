
NAME = cub3d

SRCS_FILES = cub3d.c \
		parse_input.c \
		more_parse_input.c \
		clean.c \
		error.c \
		tools.c \
		map_checker.c \
		bitmap.c \
		key_manager.c \
		rendering.c \
		movement.c \
		mlx_tools.c \
		ray_casting.c \
		ray_cast_tools.c \
		rend_sprs_tools.c 

SRCS_DIR = ./srcs/

BON_FILES = cub3d_bonus.c \
		parse_input_bonus.c \
		more_parse_input_bonus.c \
		clean_bonus.c \
		error_bonus.c \
		tools_bonus.c \
		map_checker_bonus.c \
		bitmap_bonus.c \
		key_manager_bonus.c \
		rendering_bonus.c \
		more_rendering_bonus.c \
		movement_bonus.c \
		mlx_tools_bonus.c \
		ray_casting_bonus.c \
		ray_cast_tools_bonus.c \
		rend_sprs_tools_bonus.c \
		textures_bonus.c

BON_DIR = ./bonus/

INCLDS = ./includes/

SRCS = $(addprefix $(SRCS_DIR),$(SRCS_FILES))

BONS = $(addprefix $(BON_DIR),$(BON_FILES))

OBJS = $(SRCS:.c=.o)

BON_OBJS = $(BONS:.c=.o)

CC = @gcc

RM = @rm -f

FLAGS = -Wall -Wextra -Werror -g

LIBFT = ./libft/

MLX = ./mlx/

.c.o:
	$(CC) $(FLAGS) -c -I$(INCLDS) $< -o $(<:.c=.o)

$(NAME): $(OBJS)
	@echo "generating libft lib..."
	@make -C $(LIBFT)
	@echo "compiling cub3d..."
	$(CC) $(OBJS) -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\033[0;32mready to go!"
	@echo "\033[0m"

all: $(NAME)

bonus: $(NAME) $(BON_OBJS)
	@echo "compiling cub3d bonus..."
	$(CC) $(BON_OBJS) -Lmlx -lmlx -Llibft -lft -framework OpenGL -framework AppKit -o $(NAME)
	@echo "\033[0;32mready to go!"
	@echo "\033[0m"
	./cub3d ./maps/bonus.cub

clean:
	@echo "removing all obj files..."
	@make clean -C $(LIBFT)
	$(RM) $(OBJS) $(BON_OBJS)

fclean: clean
	@echo " and cub3d"
	@make fclean -C $(LIBFT)
	$(RM) $(NAME)

re: fclean all

norme:
	norminette -R CheckForbiddenSourceHeader $(SRCS)
	norminette -R CheckDefine $(INCLDS)cub3d.h $(INCLDS)libft.h

norme_bonus:
	norminette -R CheckForbiddenSourceHeader $(BONS)
	norminette -R CheckDefine $(INCLDS)cub3d_bonus.h

.PHONY: all clean fclean re norme bonus