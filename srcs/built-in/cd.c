void cd_command(const char *path)
{
	char	buffer[1024];
	char	*new_path;
	char	*temp;

	if (path == NULL || path[0] == 0)
		return ;
	if (path[0] == '/')
	{
		if (chdir(path) != 0)
			perror("cd");
	}
	else
	{
		if (getcwd(buffer, 1024) != NULL)
		{
			temp = ft_strjoin(buffer, "/");
			new_path = ft_strjoin(temp, path);
			free(temp);
			if (chdir(path) != 0)
				perror("cd");
			free(new_path);
		}
		else
			perror("getcwd");
	}
	pwd_command();
}
