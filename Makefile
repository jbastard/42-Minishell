NAME		= minishell

#COMPILATION
CC			= cc
FLAGS		= -Wall -Wextra -Werror -lreadline -g

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
C_FILES		=	main.c \

SRC			=	$(addprefix $(SRC_DIR), $(C_FILE))
OBJ			=	$(addprefix $(OBJ_DIR), $(C_FILE:.c=.o))

#OBJ CREATION IN OBJ DIR
$(OBJ_DIR)%.o: $(SRC_DIR)%.c
	@mkdir -p $(dir $@)
	@$(CC) $(FLAG) -c $< -o $@

all : $(NAME)

#CLONE AND MAKE LIBFT
$(LIBFT_LIB):
	@if [ ! -d "$(LIBFT_PATH)" ]; then \
		git clone $(LIBFT_GIT) $(LIBFT_PATH) ${SILENT};\
	fi
	@make -C $(LIBFT_PATH) ${SILENT}

$(NAME): $(LIBFT_LIB) $(OBJ)
	@$(CC) $(FLAGS) $(OBJ) $(LIBFT_LIB) -o $(NAME)

clean :
	rm -rf $(OBJS_DIR)
	make clean -C $(LIBFT_PATH) ${SILENT}

fclean :
	rm -f $(NAME)
	rm -rf $(OBJS_DIR)
	rm -rf $(LIBFT_PATH)

re : fclean all

.PHONY: all clean fclean re