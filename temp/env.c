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
