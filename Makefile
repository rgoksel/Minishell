# COLORS
RESET 			=\033[0m
BLACK 			=\033[30m
WHITE 			=\033[37m
RED 			=\033[31m
LIGHT_RED 		=\033[91m
GREEN 			=\033[32m
LIGHT_GREEN 	=\033[92m
YELLOW 			=\033[33m
LIGHT_YELLOW 	=\033[93m
BLUE 			=\033[34m
LIGHT_BLUE 		=\033[94m
MAGENTA 		=\033[35m
LIGHT_MAGENTA 	=\033[95m
CYAN 			=\033[36m
LIGHT_CYAN 		=\033[96m
GREY 			=\033[90m
LIGHT_GREY 		=\033[37m

BLACK_BOLD 		=\033[1;30m
RED_BOLD 		=\033[1;31m
GREEN_BOLD 		=\033[1;32m
YELLOW_BOLD 	=\033[1;33m
BLUE_BOLD 		=\033[1;34m
MAGENTA_BOLD 	=\033[1;35m
CYAN_BOLD 		=\033[1;36m
WHITE_BOLD 		=\033[1;37m

# FILE
SRCS 	= main.c control.c free.c signals.c error.c add.c 
LIBFT 	= libft/ft_bzero.c libft/ft_memset.c libft/ft_calloc.c \
		  libft/ft_substr.c libft/ft_strdup.c libft/ft_strlen.c \
		  libft/ft_strjoin.c libft/ft_strncmp.c libft/ft_split.c \
		  libft/ft_strchr.c  libft/ft_strlcpy.c libft/ft_strcmp.c \
		  libft/ft_atoi.c libft/ft_itoa.c libft/ft_strcpy.c

TOKEN	= token/tokenize.c 
LEXER	= lexer/lexerize.c lexer/quote.c lexer/dollar.c lexer/dollar_two.c
BUILT 	= builtin/pwd.c builtin/builtin.c builtin/cd.c builtin/exit.c \
		  builtin/env.c builtin/echo.c builtin/unset.c builtin/export.c \
		  builtin/export_two.c
CMD		= cmd/cmd.c cmd/path.c
RED		= redirect/heredoc.c redirect/fd.c redirect/redirect.c
LIST	= lst/token_lst.c lst/lst_export.c lst/lst_env.c lst/process_lst.c

# COMMAND
SUCCESS		=	@printf "$(GREEN_BOLD)BUILD SUCCESSFULL !$(RESET)\n"
O_REMOVE	=	@printf "$(RED_BOLD).o files Deleted !$(RESET)\n"
M_REMOVE	=	@printf "$(RED_BOLD)Minishell file Deleted !$(RESET)\n"

# VARIABLES
NAME		=	minishell
OBJ			=	$(SRCS:%.c=%.o)  	\
				$(LIBFT:%.c=%.o) 	\
				$(TOKEN:%.c=%.o) 	\
				$(LEXER:%.c=%.o) 	\
				$(CMD:%.c=%.o) 		\
				$(LIST:%.c=%.o)		\
				$(RED:%.c=%.o) 		\
				$(BUILT:%.c=%.o)	

CC			=	@gcc
CFLAGS		=	-Wall -Wextra -Werror
READLINE	=	-lreadline
RM			=	rm -rf


all: $(NAME)

$(NAME)	:	$(OBJ)
			@echo "\n"
			$(CC) $(CFLAGS) $(OBJ) -o $(NAME) $(READLINE)
			$(SUCCESS)

%.o		: 	%.c
			@printf "$(CYAN_BOLD)GENERATE $(RESET)%-33.33s\r" $@
			@${CC} ${CFLAGS} -c $< -o $@

clean	:
			$(RM) $(OBJ)
			$(O_REMOVE)

fclean	:	clean
			$(RM) $(NAME)
			$(M_REMOVE)

re		:	fclean all

.PHONY: all re clean fclean