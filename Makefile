NAME	= minishell

SRCS	= minishell.c open_term.c init_paths.c exec_cmd.c prompt_msg.c \
ft_builtins.c ft_echo.c ft_pwd.c ft_cd.c init_newargv.c ft_cmd.c tools.c \
ft_read_input.c ft_export.c ft_free.c

SRCS_P	= convert_hexa.c ft_printf_fd.c print_d.c print_s.c print_x.c tools.c

OBJS	= $(SRCS:.c=.o)

_SRCS_P	= ${addprefix Printf/, ${SRCS_P}}

OBJS_P	= $(_SRCS_P:.c=.o)

CFLAGS	= -Wall -Werror -Wextra

FLAGS	= -lreadline -L/Users/$(UNAME)/.brew/Cellar/readline/8.1/lib/ -I/Users/$(UNAME)/.brew/Cellar/readline/8.1/include

%.o: %.c
			gcc -g $(CFLAGS) $(INC) -o $@ -c $?

all:	$(NAME)

RM		= rm -rf

INC		= -I includes/

lib:	
	make -C Libft

$(NAME):	lib $(OBJS) $(OBJS_P)
		gcc -g $(CFLAGS) $(OBJS) $(OBJS_P) $(FLAGS) -o $(NAME) Libft/libft.a

clean:
		$(RM) $(OBJS) $(OBJS_P)

fclean:		clean
			$(RM) $(NAME)
			make fclean -C Libft

re:		fclean all

.PHONY:		all clean fclean re
