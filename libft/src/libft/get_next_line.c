/* ************************************************************************** */
/*																			*/
/*														:::	  ::::::::   */
/*   get_next_line.c									:+:	  :+:	:+:   */
/*													+:+ +:+		 +:+	 */
/*   By: nlecreux <nlecreux@student.42.fr>		  +#+  +:+	   +#+		*/
/*												+#+#+#+#+#+   +#+		   */
/*   Created: 2024/11/08 21:41:11 by nlecreux		  #+#	#+#			 */
/*   Updated: 2024/11/08 22:42:29 by nlecreux		 ###   ########.fr	   */
/*																			*/
/* ************************************************************************** */

#include "../../include/get_next_line.h"
#include "../../include/libft.h"

char	*get_linel(int fd, char *buf, char *backup)
{
	int		read_line;
	char	*char_temp;

	read_line = 1;
	while (read_line != 0)
	{
		read_line = read(fd, buf, BUFFER_SIZE);
		if (read_line == -1)
			return (NULL);
		if (read_line == 0)
			break ;
		buf[read_line] = '\0';
		if (!backup)
			backup = ft_strdup("");
		char_temp = backup;
		backup = ft_strjoin(char_temp, buf);
		free(char_temp);
		char_temp = NULL;
		if (!backup)
			return (NULL);
		if (ft_strchr (buf, '\n'))
			break ;
	}
	return (backup);
}

char	*get_backup(char *line)
{
	size_t	count;
	char	*backup;

	count = 0;
	while (line[count] != '\n' && line[count] != '\0')
		count++;
	if (line[count] == 0)
		return (NULL);
	backup = ft_substr(line, count + 1, ft_strlen(line) - count);
	if (backup[0] == 0)
	{
		free(backup);
		backup = NULL;
	}
	line[count + 1] = '\0';
	return (backup);
}

char	*get_next_line(int fd)
{
	char		*line;
	char		*buf;
	static char	*backup;

	if (fd < 0 || fd > 1024 || BUFFER_SIZE <= 0)
		return (NULL);
	buf = malloc(BUFFER_SIZE + 1);
	if (!buf)
		return (NULL);
	line = get_linel(fd, buf, backup);
	free(buf);
	buf = NULL;
	if (!line && backup)
	{
		free(backup);
		backup = NULL;
	}
	if (!line)
		return (NULL);
	backup = get_backup(line);
	return (line);
}

/* int	main()
{
	int	fd = open("test.txt" , O_RDONLY);
	int	i = 1;
	while(i < 6)
	{
	char *line = get_next_line(fd);
	printf("Ligne %d : %s", i, line);
	free(line);
	i++;
	}
	close(fd);
} */