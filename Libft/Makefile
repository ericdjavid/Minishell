NAME	= libft.a

SRCS	= ft_strdup.c free_matc.c ft_strlen.c print_matc.c ft_strncmp.c\
ft_strcat.c ft_strcpy.c ft_split.c ft_matlen.c free_3dim_matc.c ft_strchr.c

OBJS	= $(SRCS:.c=.o)

CC		= cc

AR		= ar rc

RM		= rm -rf

INC		= -I includes/

CFLAGS	= -Wall -Werror -Wextra 

%.o: %.c
		$(CC) $(CFLAGS) $(INC) -o $@ -c $?

$(NAME):	$(OBJS)
		ar rc $(NAME) $(OBJS)
		ranlib $(NAME)

all:		$(NAME)

clean:
			$(RM) $(OBJS)

fclean:		clean
			$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
