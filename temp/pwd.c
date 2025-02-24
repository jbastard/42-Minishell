int	pwd_command(char **args)
{
	(void)args;
	char	buffer[1024];
	getcwd(buffer, 1024);
	printf("%s\n", buffer);
	return (0);
}
