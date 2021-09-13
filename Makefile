CC = clang

NAME = philosopher.a

FLAGS = -Wall -Wextra -Werror

SRCS  =   srcs/utils.c srcs/error.c srcs/status.c srcs/setup.c srcs/routine.c\


RM	= rm -f

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@$(CC) -g -fsanitize=address philosopher.c -o philo philosopher.a

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) philo

re: fclean all