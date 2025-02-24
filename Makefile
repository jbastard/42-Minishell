NAME		= minishell

#COMPILATION
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lreadline

#FILES DIRECTORIES
SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJS_DIR	=	objs/
CORE_DIR	=	core/
ERROR_DIR	=	error/
PARSING_DIR	=	parsing/
BUILT-IN_DIR=	built-in/

#LIBFT
LIBFT_GIT	=	https://github.com/jbastard/42-Libft.git
LIBFT_PATH	=	libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

#SRCS FILES
C_FILES		=	$(CORE_DIR)main.c \
				$(ERROR_DIR)error_handler.c \
				$(PARSING_DIR)signal_handler.c \
				$(PARSING_DIR)cmd_parsing.c \
				$(BUILT-IN_DIR)echo.c

SRC			=	$(addprefix $(SRC_DIR), $(C_FILES))
OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

$(OBJS_DIR)%.o: $(SRC_DIR)%.c | $(OBJS_DIR)
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

$(OBJS_DIR):
	@mkdir -p $(OBJS_DIR)

all : $(NAME)

#CLONE AND MAKE LIBFT
$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_PATH)" ]; then \
		git clone $(LIBFT_GIT) $(LIBFT_PATH); \
	fi
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) $(LFLAGS)

clean :
	rm -rf $(OBJS_DIR)
	rm -rf $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)

re : fclean all

.PHONY: all clean fclean re