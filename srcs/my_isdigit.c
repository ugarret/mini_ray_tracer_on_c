#include "../includes/mylib.h"

int	my_isdigit(int smbl)
{
	if (smbl >= 48 && smbl <= 57)
		return (1);
	else
		return (0);
}
