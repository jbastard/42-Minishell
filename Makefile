NAME		= minishell

#COMPILATION
CC			= clang
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lreadline

#VISUAL
MAKEFLAGS		+= --no-print-directory
RM_LINE			= @tput cuu1 && tput el

BLUE			= \033[0;34m
BOLD_BLUE		= \e[1;94m
GREEN			= \033[0;92m
DEF_COLOR		= \033[0;39m

#FILES DIRECTORIES
SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJS_DIR	=	objs/
CORE_DIR	=	core/
ERROR_DIR	=	error/
PARSING_DIR	=	parsing/
BUILT-IN_DIR=	built_in/
EXEC_DIR	=	exec/
LEXING_DIR	=	lexing/

#LIBFT
LIBFT_PATH	=	libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

#SRCS FILES
C_FILES		=	$(CORE_DIR)init.c \
				$(CORE_DIR)main.c \
				$(CORE_DIR)prompt.c \
				$(EXEC_DIR)handle_commands.c \
				$(EXEC_DIR)heredoc.c \
				$(EXEC_DIR)handle_redir.c \
				$(EXEC_DIR)exec_utils.c \
				$(EXEC_DIR)exec_multiple_cmd.c \
				$(ERROR_DIR)error_handler.c \
				$(ERROR_DIR)all_kinds_of_free.c \
				$(PARSING_DIR)signal_handler.c \
				$(PARSING_DIR)cmd_parsing.c \
				$(PARSING_DIR)cmd_parsing_utils.c \
				$(PARSING_DIR)syntax_checker.c \
				$(PARSING_DIR)path_finder.c \
				$(LEXING_DIR)line_lexer.c \
				$(LEXING_DIR)quotes_lexer.c \
				$(LEXING_DIR)utils_lexer.c \
				$(LEXING_DIR)lexer_main_loop.c \
				$(LEXING_DIR)handle_env_var.c \
				$(BUILT-IN_DIR)cd.c \
				$(BUILT-IN_DIR)echo.c \
				$(BUILT-IN_DIR)env.c \
				$(BUILT-IN_DIR)exit.c \
				$(BUILT-IN_DIR)export.c \
				$(BUILT-IN_DIR)pwd.c \
				$(BUILT-IN_DIR)unset.c \
				$(BUILT-IN_DIR)mordex.c \
				$(BUILT-IN_DIR)bi_utils_env0.c \
				$(BUILT-IN_DIR)bi_utils_env1.c \
				$(BUILT-IN_DIR)bi_utils_env2.c \

SRC			=	$(addprefix $(SRC_DIR), $(C_FILES))
OBJS		=	$(patsubst $(SRC_DIR)%.c, $(OBJS_DIR)%.o, $(SRC))

$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@echo "Compiling $< into $@..."
	@$(CC) $(CFLAGS) -c $< -o $@
	@${RM_LINE}

all : $(NAME)

$(LIBFT_LIB):
	@make -C $(LIBFT_PATH)

$(NAME): $(LIBFT_LIB) $(OBJS)
	@$(CC) $(CFLAGS) $(OBJS) $(LIBFT_LIB) -o $(NAME) $(LFLAGS)
	@echo "${BLUE}Done creating [ ${BOLD_BLUE}${NAME}${BLUE} ]${DEF_COLOR}"

clean :
	@echo "Removing ${NAME} and dependencies..."
	@rm -rf $(OBJS_DIR)
	@make fclean -C $(LIBFT_PATH)

fclean : clean
	@rm -f $(NAME)

re : fclean all

.PHONY: all clean fclean re
