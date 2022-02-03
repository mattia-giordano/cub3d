
NAME	= libft.a

SRCS	= ft_atoi.c \
			ft_check_ext.c \
			ft_gnl.c \
			ft_is_in_string.c \
			ft_strcmp.c \
			ft_strdup.c \
			ft_strjoin.c \
			ft_strlen.c \
			ft_itoa.c

OBJS	= $(SRCS:.c=.o)

CC		= @gcc

RM		= @rm -f

FLAGS	= -Wall -Wextra -Werror

AR		= @ar rc

.c.o:
			$(CC) $(FLAGS) -c $< -o $(<:.c=.o)

$(NAME):	$(OBJS)
			$(AR) $(NAME) $(OBJS)
			@ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re	

