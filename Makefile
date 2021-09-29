CC = clang

NAME = philosopher.a

FLAGS = -Wall -Wextra -Werror

LINK = -pthread

SRCS  =   srcs/utils.c srcs/error.c srcs/status.c srcs/setup.c srcs/routine.c srcs/init_philos.c\


RM	= rm -f

OBJS = $(SRCS:.c=.o)

.c.o:
	$(CC) $(FLAGS) -c $< -o $@

all: $(NAME)

$(NAME): $(OBJS)
	@ar rcs $(NAME) $(OBJS)
	@ranlib $(NAME)
	@$(CC) $(LINK) philosopher.c -o philo philosopher.a

clean:
	$(RM) $(OBJS)

fclean:	clean
	$(RM) $(NAME)
	$(RM) philo

re: fclean all
