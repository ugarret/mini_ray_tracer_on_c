#include "../includes/mylib.h"

int	my_strncmp(const char *str1, const char *str2, size_t n)
{
	size_t i;

	if (!str1)
		return (-1);
	if (!str2)
		return (1);
	i = 0;
	while ((str1[i] || str2[i]) && i < n)
	{
		if (str1[i] != str2[i])
			return ((unsigned char)str1[i] - (unsigned char)str2[i]);
		i++;
	}
	return (0);
}
