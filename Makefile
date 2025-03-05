NAME		= minishell

#COMPILATION
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lreadline

#VISUAL
MAKEFLAGS		+= --no-print-directory

#FILES DIRECTORIES
SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJS_DIR	=	objs/
CORE_DIR	=	core/
ERROR_DIR	=	error/
PARSING_DIR	=	parsing/
BUILT-IN_DIR=	built_in/
UTILS_DIR	=	utils/
EXEC_DIR	=	exec/
LEXING_DIR	=	lexing/

#LIBFT
LIBFT_PATH	=	libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

#SRCS FILES
C_FILES		=	$(CORE_DIR)main.c \
				$(CORE_DIR)init.c \
				$(EXEC_DIR)handle_commands.c \
				$(ERROR_DIR)error_handler.c \
				$(PARSING_DIR)signal_handler.c \
				$(PARSING_DIR)cmd_parsing.c \
				$(LEXING_DIR)line_lexer.c \
				$(LEXING_DIR)utils_lexer.c \
				$(BUILT-IN_DIR)cd.c \
				$(BUILT-IN_DIR)echo.c \
				$(BUILT-IN_DIR)env.c \
				$(BUILT-IN_DIR)exit.c \
				$(BUILT-IN_DIR)export.c \
				$(BUILT-IN_DIR)pwd.c \
				$(BUILT-IN_DIR)unset.c \
				$(BUILT-IN_DIR)mordex.c \
				$(UTILS_DIR)utils0.c

SRC			=	$(addprefix $(SRC_DIR), $(C_FILES))
OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(CFLAGS) -c $< -o $@

all : $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT_LIB) $(OBJS)
	$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) $(LFLAGS)

clean :
	@rm -rf $(OBJS_DIR)
	@make fclean -C $(LIBFT_PATH)

fclean : clean
	rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re