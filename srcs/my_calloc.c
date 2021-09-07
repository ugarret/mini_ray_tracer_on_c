#include "../includes/mylib.h"

void	*my_calloc(size_t count, size_t size)
{
	void *pointer;

	if (!(pointer = (void *)malloc(count * size)))
		return (NULL);
	my_bzero(pointer, count * size);
	return (pointer);
}
