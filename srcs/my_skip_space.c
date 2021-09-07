#include "../includes/mylib.h"

char	*my_skip_space(char *line)
{
	if (!line)
		return (NULL);
	while (*line == ' ' || (*line > 8 && *line < 13) || *line == '\r')
		line++;
	return (line);
}
