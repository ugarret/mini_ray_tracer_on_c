#include "../includes/mylib.h"

void	*my_memset(void *memptr, int val, size_t len)
{
	size_t i;

	i = 0;
	while (i < len)
	{
		*(unsigned char *)(memptr + i) = (unsigned char)val;
		i++;
	}
	return (memptr);
}
