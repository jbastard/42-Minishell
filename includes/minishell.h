/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:19:18 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/17 09:17:17 by jbastard         ###   ########.fr       */
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

extern volatile	int g_sig;

typedef struct s_minishell t_minishell;
typedef struct s_builtin t_builtin;
typedef struct s_cmd t_cmd;
typedef struct s_var t_var;
typedef	struct s_token t_token;
typedef struct s_redir t_redir;

typedef enum e_token_type
{
	TOKEN_EMPTY,
	TOKEN_WORD,
	TOKEN_PIPE,
	TOKEN_REDIR_OUT,
	TOKEN_REDIR_IN,
	TOKEN_HEREDOC,
	TOKEN_APPEND,
}	t_token_type;

typedef enum e_error_type
{
	ERR_NONE,
	ERR_MALLOC,
	ERR_SYNTAX,
	ERR_CMD_NOT_FOUND,
	ERR_PERMISSION_DENIED,
	ERR_EXEC_FAIL,
	ERR_EXIT,
	ERR_SIGNAL,
	ERR_PIPE,
	ERR_REDIR,
}	t_error_type;

struct s_redir {
	int		type;
	char	*file;
	int		fd;
	t_redir	*next;
};

struct s_cmd {
	char	**cmd_args;
	char	*path;
	t_redir	*redir;
	int 	fd_in;
	int 	fd_out;
	t_cmd	*next;
};

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
	t_cmd		*cmd;
	char 		*line;
	char		**env;
	char		*prompt;
	int			last_status;
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
	int 		error;
} t_lexer;

void	print_tokens(t_token *toks);

void	sig_handler(void);

//ERROR
	//ERROR_HANDLER.C
void 	exit_error(char *source, int isper, int isexit);
int		handle_error(t_minishell *main, t_error_type type, char *info);
void 	free_cmd(t_cmd *cmd);
void 	free_redir(t_redir *redir);

//PARSING
	//SIGNAL_HANDLER.C
void	signal_handler();
void	ctrl_c(int signal);
	//CMD_PARSING.C
char	*get_cmd(t_minishell *main, char *line);
t_cmd	*parse_tokens(t_minishell *main);
t_cmd	*create_cmd(t_token **toks);
int		parse_cmd_into_tokens(t_cmd *cmd, t_token **toks);
void	add_redir(t_redir **head, int type, char *file);
	//CMD_PARSING_UTILS.C
int 	add_cmds(t_cmd	**head, t_token **toks);
int		alloc_args(t_cmd *cmd, int argcount);
int		is_redir(t_token *toks);
int 	args_count(t_token *toks);
void 	init_cmd(t_cmd *new);
	//SYNTAX_CHECKER
int 	syntax_checker(t_minishell *main);
int 	check_redirs(t_minishell *main);
int 	check_pipes(t_minishell *main);

	//PROMPT.c
int		count_chars_tab(char **tabl);
char	*better_join(char **tabl, char sep);
void	update_prompt(t_minishell *main);

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
t_token *lexer(char *line, t_minishell *main);
void 	free_lexer(t_token *token);
	//UTILS_LEXER.C
void 	add_redirection_token(t_lexer *lexer, char c);
void 	handle_env_var(t_lexer *lexer);
void 	handle_single_quotes(t_lexer *lexer);
void 	handle_double_quotes(t_lexer *lexer);
void 	handle_special_char_op(t_lexer *lexer);

#endif
