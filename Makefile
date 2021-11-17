NAME	= minishell

SRCS	= minishell.c open_term.c init_paths.c exec_cmd.c prompt_msg.c \
ft_builtins.c ft_echo.c ft_pwd.c ft_cd.c

SRCS_P	= convert_hexa.c ft_printf_fd.c print_d.c print_s.c print_x.c tools.c

OBJS	= $(SRCS:.c=.o)

_SRCS_P	= ${addprefix Printf/, ${SRCS_P}}

OBJS_P	= $(_SRCS_P:.c=.o)

FLAGS	= -Wall -Werror -Wextra

%.o: %.c
			cc $(FLAGS) $(INC) -o $@ -c $?

all:	$(NAME)

RM		= rm -rf

INC		= -I includes/

lib:	
	make -C Libft

$(NAME):	lib $(OBJS) $(OBJS_P)
		gcc $(FLAGS) -lreadline $(OBJS) $(OBJS_P) -o $(NAME) Libft/libft.a

clean:
		$(RM) $(OBJS) $(OBJS_P)

fclean:		clean
			$(RM) $(NAME)
			make fclean -C Libft

re:		fclean all

.PHONY:		all clean fclean re
