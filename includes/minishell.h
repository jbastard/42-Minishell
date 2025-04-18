/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: jbastard <jbastard@student.1337.ma>        +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/03/26 15:26:12 by jbastard          #+#    #+#             */
/*   Updated: 2025/04/15 09:31:27 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL_H
# define MINISHELL_H

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
# define SIG_INTER 1 
# define SIG_EXEC 2
# define SIG_CHILD 3 
# define ERROR_NUM_ARGS "minishell: exit: numeric argument required\n"

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
	ERR_FILE_NOT_FOUND,
	ERR_PERMISSION_DENIED,
	ERR_EXEC_FAIL,
	ERR_EXIT,
	ERR_SIGNAL,
	ERR_PIPE,
	ERR_REDIR,
}	t_error_type;

extern volatile int			g_signal;

typedef struct s_minishell	t_minishell;
typedef struct s_builtin	t_builtin;
typedef struct s_cmd		t_cmd;
typedef struct s_token		t_token;
typedef struct s_redir		t_redir;
typedef struct s_env		t_env;
typedef struct s_lexer		t_lexer;

struct s_redir
{
	int		type;
	char	*file;
	int		fd;
	t_redir	*next;
};

struct s_cmd
{
	char	**cmd_args;
	char	*path;
	t_redir	*redir;
	t_cmd	*next;
};

struct s_builtin
{
	char	*cmd_name;
	int		(*cmd)(char **, t_minishell *);
};

struct s_minishell
{
	t_builtin	*builtins;
	t_env		*local_vars;
	char		**env;
	char		*prompt;
	char		*line;
	t_cmd		*cmd;
	t_token		*tokens;
	int			last_status;
	int			is_here;
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

struct s_token
{
	char			*value;
	int				type;
	struct s_token	*next;
};

struct s_lexer
{
	const char	*input;
	size_t		input_len;
	t_token		*tokens;
	char		buffer[1024];
	int			i;
	int			j;
	char		quote;
	int 		error;
};

int			handle_redir(t_minishell *main, t_cmd *cmd);
int			heredoc(t_minishell *main, char *file, char *tmp_name);
char		*generate_tmp_name(int i);
void		preprocess_heredocs(t_minishell *main, t_cmd *cmds);

//ERROR
	//ERROR_HANDLER.C
void		exit_error(char *source, int isper, int isexit);
int			handle_error(t_minishell *main, t_error_type type, char *info);
void		handle_error1(t_minishell *main, t_error_type type, char *info);
	//ALL_KINDS_OF_FREE.C
void		free_cmd(t_cmd *cmd);
void		free_redir(t_redir *redir);
void		free_tab(char **tabl);
void		free_lexer(t_token *token);
void		free_local_env(t_env **env);

//BUILT-INS
	//CD.C
int			cd_command(char **args, t_minishell *main);
	//ECHO.C
int			echo_command(char **args, t_minishell *main);
	//ENV.C
int			env_command(char **args, t_minishell *main);
	//EXIT.C
int			exit_command(char **args, t_minishell *main);
	//EXPORT.C
char		**change_env(char *env, t_minishell *main);
int			export_command(char **args, t_minishell *main);
int			find_node_env(char *env, t_minishell *main);
void		replace_value_env(char *env, t_minishell *main);
	//MORDEX.C
int			mordex_command(char **args, t_minishell *main);
	//PWD.C
int			pwd_command(char **args, t_minishell *main);
	//UNSET.C
int			unset_command(char **args, t_minishell *main);
	//BI_UTILS_ENV0.C
void		add_node_env(char *env, t_minishell *main);
t_env		*create_env_node(char *env);
void		print_locals(t_minishell *main);
	//BI_UTILS_ENV1.C
int			check_env(char *env, t_minishell *main);
char		**ft_realloc_tab(char **args, char *env);
int			is_valid_identifier(const char *name);
int			len_equal(char	*env);
char		**copy_env(void);
	//BI_UTILS_ENV2.c
void		insert_sorted(t_env **sorted, t_env *new_node);
void		sort_local_env(t_env **locals);
int			count_args(char **args);
int			is_special_char(char c);
int			is_whitespaces(char c);

//CORE
	//INIT.C
t_builtin	*init_builtins(void);
void		init_local_env(t_minishell *main);
t_minishell	init_minishell(void);
void		init_lexer(t_lexer *lexer, const char *input);
	//PROMPT.C
char		*better_join(char **tabl, char sep);
int			count_chars_tab(char **tabl);
void		update_prompt(t_minishell *main);

//PARSING
	//SIGNAL_HANDLER.C
void		sig_handler(void);
void		ctrl_c(int signal);
void		set_sig_interactive(void);
void		set_sig_executing(void);

	//CMD_PARSING.C
int			get_cmd(t_minishell *main);
t_cmd		*parse_tokens(t_minishell *main);
t_cmd		*create_cmd(t_token **toks);
int			parse_cmd_into_tokens(t_cmd *cmd, t_token **toks);
void		add_redir(t_redir **head, int type, char *file);
	//CMD_PARSING_UTILS.C
int			add_cmds(t_cmd	**head, t_token **toks);
int			alloc_args(t_cmd *cmd, int argcount);
int			is_redir(t_token *toks);
int			args_count(t_token *toks);
void		init_cmd(t_cmd *new);
	//SYNTAX_CHECKER
int			syntax_checker(t_minishell *main);
int			check_redirs(t_minishell *main);
int			check_pipes(t_minishell *main);
	//PATH_FINDER.C
int			check_cmd(t_minishell *main);

//EXEC
	//HANDLE_COMMANDS.C
void		handle_commands(t_cmd *cmds, t_minishell *main);
void		exec_one_cmd(t_cmd *cmd, t_minishell *main);
void		exec_multiple_cmds(t_cmd *cmds,
				t_minishell *main,
				int prev_pipe);
	//EXEC_UTILS.C
int			is_builtin(t_builtin *builtins, char *cmd);
int			count_commands(t_cmd *cmds);
void		create_pipe_and_fork(t_cmd *cmds,
				t_minishell *main,
				int prev_pipe,
				int pipefd[2],
				int *pid);
void		execute_external_command(t_cmd *cmd, t_minishell *main);

//LEXING
	//LINE_LEXER.C
t_token		*new_token(char *value, int type);
void		add_token(t_token **head, char *value, int type);
void		handle_buffer(t_lexer	*lexer);
t_token		*lexer(char *line, t_minishell *main);
void		add_redirection_token(t_lexer *lexer, char c);
	//UTILS_LEXER.C
char		*ft_getenv(char *env, t_minishell *main);
int			get_equals(char *env);
void		add_double_token(t_lexer *lexer, char c);
void		handle_special_char_op(t_lexer *lexer);
//QUOTES_LEXER.C
void		error_var(t_lexer *lexer,
				t_minishell *main,
				char *env_value,
				int k);
void		handle_env_var(t_lexer *lexer, t_minishell *main);
void		handle_single_quotes(t_lexer *lexer);
void		handle_double_quotes(t_lexer *lexer, t_minishell *main);

#endif
