void	pwd_command(void)
{
	char	buffer[1024];
	getcwd(buffer, 1024);
	printf("%s\n", buffer);
}
