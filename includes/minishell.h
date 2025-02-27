/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   minishell.h                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: nlecreux <nlecreux@student.42.fr>          +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2025/02/22 17:19:18 by nlecreux          #+#    #+#             */
/*   Updated: 2025/02/26 15:38:26 by jbastard         ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

#ifndef MINISHELL
# define MINISHELL

# define _POSIX_C_SOURCE 200809L

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
	t_cmd		*cmd;
	char		**env;
	char		*prompt;
};

struct	s_cmd {
	int		id;
	char	*cmd_path;
	char	**args;
	t_cmd	*next;
};

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
// int	export_command(char **args, t_minishell *main);
	//PWD.C
int		pwd_command(char **args, t_minishell *main);
	//UNSET.C
// int	unset_command(char **args, t_minishell *main);

//CORE
	//INIT.C
t_minishell	init_minishell(void);
char		**copy_env(void);
t_builtin	*init_builtins(void);

//UTILS
	//UTILS0.C
int		count_args(char **args);
void	free_tab(char **tabl);

//EXEC
	//HANDLE_COMMANDS.C
void	handle_commands(char **args, t_minishell *main);

#endif
