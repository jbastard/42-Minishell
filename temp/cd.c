int	cd_command(char **args)
{
	(void)args;
	char	buffer[1024];
	char	*new_path;

	if (path == NULL || path[0][0] == 0)
		return ;
	if (path[0][0] == '/')
	{
		if (chdir(path[0]) != 0)
			perror("cd");
	}
	else
	{
		if (getcwd(buffer, 1024) != NULL)
		{
			new_path = ft_strjoin(buffer, "/");
			new_path = ft_strjoin(new_path, path[0]);
			if (chdir(new_path) != 0)
				perror("cd");
			free(new_path);
		}
		else
			perror("getcwd");
	}
	return (0);
}
