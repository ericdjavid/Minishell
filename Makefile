# Colors
C_GREY		=	\e[1;30m
C_RED		=	\e[1;31m
C_GREEN		=	\e[1;32m
C_YELLOW	=	\e[1;33m
C_BLUE		=	\e[1;34m
C_PURPLE	=	\e[1;35m
C_CYAN		=	\e[1;36m
C_WHITE		=	\e[1;37m
C_END		=	\e[0m

NAME	= minishell

SRCS	= minishell.c init_paths.c exec_cmd.c prompt_msg.c \
ft_builtins.c ft_echo.c ft_pwd.c ft_cd.c init_newargv.c ft_cmd.c tools.c \
ft_read_input.c ft_export.c ft_free.c ft_redirection.c ft_ascii_order.c \
ft_linked_lists.c ft_manage_fds.c ft_child.c ft_exit.c \
ft_unset.c tools2.c ft_clear.c tools3.c \

SRCS_P	= convert_hexa.c ft_printf_fd.c print_d.c print_s.c print_x.c tools.c

OBJS	= $(SRCS:.c=.o)

_SRCS_P	= ${addprefix Printf/, ${SRCS_P}}

OBJS_P	= $(_SRCS_P:.c=.o)

CFLAGS	= -Wall -Wextra -Werror

READLINE	= -lreadline

%.o: %.c
			gcc -g $(CFLAGS) $(INC) -o $@ -c $?

all:	$(NAME)

RM		= rm -rf

INC		= -I includes/

$(NAME):
	@echo "$<[$(C_PURPLE)COMPILING$(C_END)]"
	@make -C Libft
	@gcc -g $(CFLAGS) -o $(NAME) $(SRCS) $(_SRCS_P) Libft/libft.a $(READLINE)
	@echo "$<[$(C_GREEN)OK$(C_END)]"
	@echo "        _       _     _          _ _"
	@echo "  /\/\ (_)_ __ (_)___| |__   ___| | |"
	@echo " /    \| | '_ \| / __| '_ \ / _ \ | |"
	@echo "/ /\/\ \ | | | | \__ \ | | |  __/ | |"
	@echo "\/    \/_|_| |_|_|___/_| |_|\___|_|_|"
	@echo "       _"
	@echo "  __ _| |__  _ __ _   _ _ __"
	@echo " / _  |  _ \|  __| | | |  _ \ "
	@echo "| (_| | |_) | |  | |_| | | | |"
	@echo " \__,_|_.__/|_|   \__,_|_| |_|"
	@echo "          _  _             _     _"
	@echo "  ___  __| |(_) __ ___   _(_) __| |"
	@echo " / _ \/ _  || |/ _  \ \ / / |/ _  |"
	@echo "|  __/ (_| || | (_| |\ V /| | (_| |"
	@echo " \___|\__,_|/ |\__,_| \_/ |_|\__,_|"
	@echo "          |__/"

clean:
	@echo "$<[$(C_YELLOW)Cleaning .o files$(C_END)]"
	@$(RM) $(OBJS) $(OBJS_P)
	@make fclean -C Libft
	@echo "$<[$(C_GREEN)OK$(C_END)]"

fclean:		clean
	@$(RM) $(NAME)
	@make fclean -C Libft

re:		fclean all

.PHONY:		all clean fclean re


