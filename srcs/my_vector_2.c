#include "../includes/rtmini.h"

double		my_lenght_vector(t_vector v)
{
	return (sqrt(v.x * v.x + v.y * v.y + v.z * v.z));
}

t_vector	my_add(t_vector v1, t_vector v2)
{
	return (my_new_vector(v1.x + v2.x, v1.y + v2.y, v1.z + v2.z));
}

t_vector	my_sub(t_vector v1, t_vector v2)
{
	return (my_new_vector(v1.x - v2.x, v1.y - v2.y, v1.z - v2.z));
}

t_vector	my_mylt_num(t_vector v, double num)
{
	return (my_new_vector(v.x * num, v.y * num, v.z * num));
}

t_vector	my_mult_two_vectors(t_vector v1, t_vector v2)
{
	return (my_new_vector(v1.x * v2.x, v1.y * v2.y, v1.z * v2.z));
}
