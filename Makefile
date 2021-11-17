NAME	= minishell

SRCS	= minishell.c open_term.c init_paths.c exec_cmd.c prompt_msg.c

OBJS	= $(SRCS:.c=.o)

FLAGS	= -Wall -Werror -Wextra

%.o: %.c
			cc $(FLAGS) $(INC) -o $@ -c $?

all:	$(NAME)

RM		= rm -rf

INC		= -I includes/

lib:	
	make -C Libft

$(NAME):	lib $(OBJS)
		gcc $(FLAGS) -lreadline $(OBJS) -o $(NAME) Libft/libft.a

clean:
		$(RM) *.o

fclean:		clean
			$(RM) $(NAME)
			make fclean -C Libft

re:		fclean all

.PHONY:		all clean fclean re
