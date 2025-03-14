/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:19:18 by nlecreux          #+#    #+#             */
/*   Updated: 2025/03/14 15:35:24 by nlecreux         ###   ########.fr       */
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

typedef struct s_minishell	t_minishell;
typedef struct s_builtin	t_builtin;
typedef struct s_env		t_env;

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
	int			status;
};

struct s_env
{
	char	*key;
	char	*value;
	t_env	*next;
};

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
	//BI_UTILS0.C
void		add_node_env(char *env, t_minishell *main);
t_env		*create_env_node(char *env);
void		print_locals(t_minishell *main);
void		free_local_env(t_env **env);
	//BI_UTILS1.C
int			check_env(char *env, t_minishell *main);
char		**ft_realloc_tab(char **args, char *env);
int			is_valid_identifier(const char *name);
int			len_equal(char	*env);
char		**copy_env(void);

//CORE
	//INIT.C
t_builtin	*init_builtins(void);
void		init_local_env(t_minishell *main);
t_minishell	init_minishell(void);
	//PROMPT.C
char		*better_join(char **tabl, char sep);
int			count_chars_tab(char **tabl);
void		update_prompt(t_minishell *main);

//ERROR
	//ERROR_HANDLER.C
void		exit_error(char *source, int isper, int isexit);

//PARSING
	//CMD_PARSING.C
char		*get_cmd(t_minishell *main);
	//SIGNAL_HANDLER.C
void		ctrl_c(int signal);
void		do_nothing(int signal);
void		sig_handler(void);

//EXEC
	//HANDLE_COMMANDS.C
void		handle_commands(char **args, t_minishell *main);
int			is_builtin(t_builtin *builtins, char *cmd);

//UTILS
	//UTILS0.C
int			count_args(char **args);
void		free_tab(char **tabl);

#endif
