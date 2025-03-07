/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:19:18 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/07 17:13:18 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# define _POSIX_C_SOURCE 200809L
# define MORDEX_PATH "libft/src/ft_dprintf/mordex.txt"

# include <stdio.h>
# include <stdlib.h>
# include <string.h>
# include <errno.h>
# include <unistd.h>
# include <fcntl.h>
# include <sys/types.h>
# include <sys/stat.h>
# include <sys/wait.h>
# include <signal.h>
# include <dirent.h>
# include <sys/ioctl.h>
# include <termios.h>
# include <utmp.h>
# include <term.h>
# include <readline/readline.h>
# include <readline/history.h>
# include "../libft/include/libft.h"

# define NAME "minishell"
# define SQUOTES '\''
# define DQUOTES '"'
#define TOKEN_WORD 1
#define TOKEN_PIPE 2
#define TOKEN_REDIR_IN 3
#define TOKEN_REDIR_OUT 4
#define TOKEN_HEREDOC 5
#define TOKEN_APPEND  6
#define TOKEN_SINGLE_QUOTED 7
#define TOKEN_DOUBLE_QUOTED 8
#define TOKEN_SEMICOLON 9

typedef struct s_minishell t_minishell;

typedef struct s_builtin t_builtin;
typedef struct s_cmd t_cmd;
typedef struct s_var t_var;
typedef	struct s_token t_token;
struct s_builtin {
	char	*cmd_name;
	int		(*cmd)(char **, t_minishell *);
	int		size;
};

struct	s_var {
	char			*name;
	char			*value;
	struct s_var	*next;
};

struct	s_minishell {
	t_builtin	*builtins;
	t_var		*local_vars;
	t_token		*tokens;
	char		**env;
	char		*prompt;
};

typedef struct s_token
{
	char            *value;
	int             type;
	struct s_token  *next;
}               t_token;

typedef struct s_lexer
{
	const char  *input;
	size_t		input_len;
	t_token     *tokens;
	char        buffer[1024];
	int         i;
	int         j;
	char        quote;
} t_lexer;

//ERROR
	//ERROR_HANDLER.C
void 	exit_error(char *source, int isper, int isexit);

//PARSING
	//SIGNAL_HANDLER.C
void	sig_handler();
void	do_nothing(int signal);
void	ctrl_c(int signal);
	//CMD_PARSING.C
char	*get_cmd(t_minishell *main);

//BUILT-INS
	//CD.C
int		cd_command(char **args, t_minishell *main);
	//ECHO.C
int		echo_command(char **args, t_minishell *main);
	//ENV.C
int		env_command(char **args, t_minishell *main);
	//EXIT.C
int		exit_command(char **args, t_minishell *main);
	//EXPORT.C
int	export_command(char **args, t_minishell *main);
	//PWD.C
int		pwd_command(char **args, t_minishell *main);
	//UNSET.C
int	unset_command(char **args, t_minishell *main);
	//MORDEX.C
int	mordex_command(char **args, t_minishell *main);

//CORE
	//INIT.C
t_minishell	init_minishell(void);
char		**copy_env(void);
t_builtin	*init_builtins(void);

//UTILS
	//UTILS0.C
int		count_args(char **args);
void	free_tab(char **tabl);
int		is_special_char(char c);
int 	is_whitespaces(char c);
int		check_env(char *env, t_minishell *main);
int		len_equal(char	*env);

//EXEC
	//HANDLE_COMMANDS.C
void	handle_commands(char **args, t_minishell *main);

//LEXING
	//LINE_LEXER.C
t_token *new_token(char *value, int type);
void 	add_token(t_token **head, char *value, int type);
void 	handle_buffer(t_lexer	*lexer);
void 	init_lexer(t_lexer *lexer, const char *input);
t_token	*lexer(char *input);
void 	free_lexer(t_token *token);
	//UTILS_LEXER.C
void 	add_redirection_token(t_lexer *lexer, char c);
void 	handle_env_var(t_lexer *lexer);
void 	handle_single_quotes(t_lexer *lexer);
void 	handle_double_quotes(t_lexer *lexer);
void 	handle_special_char_op(t_lexer *lexer);

#endif
