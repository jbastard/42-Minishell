NAME		= minishell

#COMPILATION
CC			= cc
CFLAGS		= -Wall -Wextra -Werror -g
LFLAGS		= -lreadline

#FILES DIRECTORIES
SRC_DIR		=	srcs/
INC_DIR		=	includes/
OBJS_DIR	=	objs/

#LIBFT
LIBFT_GIT	=	https://github.com/jbastard/42-Libft.git
LIBFT_PATH	=	libft/
LIBFT_FILE	=	libft.a
LIBFT_LIB	=	$(addprefix $(LIBFT_PATH), $(LIBFT_FILE))

#SRCS FILES
C_FILES		=	main.c

SRC			=	$(addprefix $(SRC_DIR), $(C_FILES))
OBJS		=	$(addprefix $(OBJS_DIR), $(C_FILES:.c=.o))

#OBJ CREATION IN OBJ DIR
$(OBJS_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(OBJS_DIR)
	@$(CC) $(CFLAGS) -c $< -o $@

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