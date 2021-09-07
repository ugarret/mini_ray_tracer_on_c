#include "../includes/mylib.h"

static int	my_count_word(char *str)
{
	int		i;
	int		count;

	i = 0;
	count = 0;
	while (str[i] != '\0')
	{
		if ((str[i] != ' ' && str[i] != '	' && str[i] != ',') &&
			(i == 0 || (i > 0 && (str[i - 1] == ' ' || str[i - 1] == '	' ||
			str[i - 1] == ','))))
			count++;
		i++;
	}
	return (count);
}

static char	*my_malloc_for_word(char **str)
{
	int		i;
	char	*word;
	char	*temp;

	temp = *str;
	i = 0;
	while ((temp[i] != ' ' && temp[i] != '	' && temp[i] != ',') && temp[i])
	{
		i++;
		(*str)++;
	}
	if (!(word = (char *)malloc(sizeof(char) * (i + 1))))
		return (NULL);
	word[i] = '\0';
	while (--i >= 0)
		word[i] = temp[i];
	return (word);
}

static void	my_error_malloc(char **arr, int j)
{
	while (j >= 0)
	{
		free(arr[j]);
		j--;
	}
	free(arr);
}

char		**my_split(char *str)
{
	int		j;
	char	**arr;
	int		count_word;

	if (!str)
		return (NULL);
	j = 0;
	count_word = my_count_word(str);
	arr = (char **)malloc(sizeof(char *) * (count_word + 1));
	if (!arr)
		return (NULL);
	while (j != count_word)
	{
		while ((*str == ' ' || *str == '	' || *str == ',') && *str)
			str++;
		arr[j] = my_malloc_for_word(&str);
		if (arr[j] == NULL)
		{
			my_error_malloc(arr, j);
			return (NULL);
		}
		j++;
	}
	arr[j] = NULL;
	return (arr);
}
