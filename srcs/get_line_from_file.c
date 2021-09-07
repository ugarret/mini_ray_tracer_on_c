#include "../includes/mylib.h"

static int	my_search_index_newline(const char *str)
{
	int		i;

	i = 0;
	while (str[i] != '\0')
	{
		if (str[i] == '\n')
			return (i);
		i++;
	}
	return (-1);
}

static char	*my_strjoin(char *str1, char *str2)
{
	char	*comb;
	int		len1;
	int		len2;
	int		i;

	if (!str1 || !str2)
		return (NULL);
	len1 = my_strlen(str1);
	len2 = my_strlen(str2);
	if (!(comb = (char *)malloc(sizeof(char) * (len1 + len2 + 1))))
		return (NULL);
	i = 0;
	while (i < len1)
	{
		comb[i] = str1[i];
		i++;
	}
	while (i < len1 + len2)
	{
		comb[i] = str2[i - len1];
		i++;
	}
	comb[i] = '\0';
	free(str1);
	return (comb);
}

static char	*my_memory_for_new_string(int i)
{
	char	*new_str;

	if (!(new_str = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	new_str[i] = '\0';
	i--;
	while (i >= 0)
	{
		new_str[i] = 0;
		i--;
	}
	return (new_str);
}

static int	write_in_remainder_and_line(char **rem_line, char **line)
{
	char		*temp;
	int			i;

	if ((i = my_search_index_newline(*rem_line)) != -1)
	{
		*line = my_substr(*rem_line, 0, i);
		temp = my_substr(*rem_line, i + 1, my_strlen(*rem_line + i + 1));
		free(*rem_line);
		if (!(*line) || !temp)
			return (-1);
		*rem_line = temp;
		return (1);
	}
	else
	{
		if (!(*line = my_substr(*rem_line, 0, my_strlen(*rem_line))))
			return (-1);
		free(*rem_line);
		*rem_line = NULL;
		return (0);
	}
}

int			get_line_from_file(int fd, char **line)
{
	static char *rem_line;
	int			bytes_read;
	char		buffer[BUFFER_SIZE + 1];

	if (!line || fd < 0 || read(fd, buffer, 0) == -1)
		return (-1);
	if (!(rem_line) && !(rem_line = my_memory_for_new_string(1)))
		return (-1);
	if (my_search_index_newline(rem_line) == -1)
	{
		while ((bytes_read = read(fd, buffer, BUFFER_SIZE)) > 0)
		{
			buffer[bytes_read] = '\0';
			if (!(rem_line = my_strjoin(rem_line, buffer)))
				return (-1);
			if (my_search_index_newline(rem_line) != -1)
				break ;
		}
	}
	return (write_in_remainder_and_line(&rem_line, line));
}
