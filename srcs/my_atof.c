#include "../includes/mylib.h"

static int	my_numlen(char *str)
{
	int	len;

	if (!str)
		return (0);
	len = 0;
	while (*str >= '0' && *str <= '9')
	{
		str++;
		len++;
	}
	return (len);
}

static int	my_atoi_for_atof(char **str)
{
	int				i;
	unsigned long	num;
	char			*temp;

	temp = *str;
	i = 0;
	num = 0;
	if (temp[i] == '+')
		i++;
	while (temp[i] >= '0' && temp[i] <= '9')
	{
		num = num * 10 + (temp[i] - '0');
		i++;
	}
	*str = &temp[i];
	return ((int)num);
}

double		my_atof(char *str)
{
	double	int_part;
	double	fract_part;
	int		len;
	int		sign;

	if (!str)
		return (0);
	sign = 1;
	str = my_skip_space(str);
	if (*str == '-')
	{
		sign *= -1;
		str++;
	}
	int_part = (double)my_atoi_for_atof(&str);
	if (sign == -1)
		int_part *= -1;
	if (*str != '.')
		return (int_part);
	str++;
	len = my_numlen(str);
	fract_part = (double)my_atoi_for_atof(&str);
	while (len--)
		fract_part /= 10;
	return (int_part + ((sign == 1) ? fract_part : -fract_part));
}
