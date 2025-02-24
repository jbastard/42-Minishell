#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include "libft/includes/libft.h"



// typedef struct s_minishell {
// 	s_builtin *builtins;
// }	t_minishell;

typedef struct s_builtin {
	char *cmd_name;
	int (*cmd)(char **);
	int	size;
}	t_builtin;

int	pwd_command(char **args)
{
	(void)args;
	char	buffer[1024];
	getcwd(buffer, 1024);
	printf("%s\n", buffer);
	return (0);
}

int	cd_command(char **path)
{
	char	buffer[1024];
	char	*new_path[2];

	if (path == NULL || path[2][0] == 0)
		return 1;
	if (path[2][0] == '/')
	{
		if (chdir(path[2]) != 0)
			perror("cd");
	}
	else
	{
		if (getcwd(buffer, 1024) != NULL)
		{
			new_path[0] = ft_strjoin(buffer, "/");
			new_path[1] = ft_strjoin(new_path[0], path[2]);
			free(new_path[0]);
			if (chdir(new_path[1]) != 0)
				perror("cd");
			free(new_path[1]);
		}
		else
			perror("getcwd");
	}
	return (0);
}

int	env_command(char **args)
{
	extern char **environ;
	int			i;

	(void)args;
	i = 0;
	if (environ)
	{
		while (environ[i])
		{
			printf("%s\n", environ[i]);
			i++;
		}
		return (0);
	}
	return (1);
}

t_builtin	*init_builtins(void)
{
	t_builtin	*bi;
	int	i;

	i = -1;
	bi = malloc(8 * sizeof(t_builtin));
	if (!bi)
		return (NULL);
	bi[0].cmd_name = "echo";
	// bi[0].cmd = command_echo;
	bi[1].cmd_name = "cd";
	bi[1].cmd = cd_command;
	bi[2].cmd_name = "pwd";
	// bi[2].cmd = command_pwd;
	bi[3].cmd_name = "export";
	// bi[3].cmd = command_export;
	bi[4].cmd_name = "unset";
	// bi[4].cmd = command_unset;
	bi[5].cmd_name = "env";
	bi[5].cmd = env_command;
	bi[6].cmd_name = "exit";
	// bi[6].cmd = command_exit;
	bi[7].cmd_name = NULL;
	while (++i <= 6)
		bi[i].size = ft_strlen(bi[i].cmd_name);
	return (bi);
}

void	manage_command(char **args, t_builtin *bi)
{
	int	i;

	i = 0;
	while (bi[i].cmd_name)
	{
		if (!ft_strncmp(bi[i].cmd_name, args[1], bi[i].size))
			bi[i].cmd(args);
		i++;
	}

}

int main(int ac, char **av)
{
	t_builtin	*bi = init_builtins();
	manage_command(av, bi);
	free(bi);
	// env_command(NULL);
}