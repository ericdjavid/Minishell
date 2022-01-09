NAME	= libft.a

SRCS	= ft_strdup.c free_matc.c ft_strlen.c print_matc.c ft_strncmp.c\
ft_strcat.c ft_strcpy.c ft_split.c ft_matlen.c free_3dim_matc.c ft_strchr.c \
ft_strjoin_free_n.c ft_strnstr.c ft_matstr.c free_mati.c ft_putnbr_fd.c\
ft_3dimlen.c ft_strjoin.c ft_str_is_num.c ft_atoi.c ft_isdigit.c \
ft_split_utils.c

OBJS	= $(SRCS:.c=.o)

CC		= gcc -g

AR		= ar rc

RM		= rm -rf

INC		= -I includes/

CFLAGS	= -Wall -Werror -Wextra

%.o: %.c
	@$(CC) $(CFLAGS) $(INC) -o $@ -c $?

$(NAME):	$(OBJS)
	@ar rc $(NAME) $(OBJS)
	@ranlib $(NAME)

all:		$(NAME)

clean:
	@$(RM) $(OBJS)

fclean:		clean
	@$(RM) $(NAME)

re:			fclean all

.PHONY:		all clean fclean re
