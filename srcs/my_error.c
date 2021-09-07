#include "../includes/rtmini.h"

void	my_error(char *message)
{
	write(2, "Error\n", 6);
	write(2, &*message, my_strlen(message));
	write(2, "\n", 1);
	exit(1);
}
