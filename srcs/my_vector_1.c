#include "../includes/rtmini.h"

t_vector	my_new_vector(double x, double y, double z)
{
	t_vector new_vector;

	new_vector.x = x;
	new_vector.y = y;
	new_vector.z = z;
	return (new_vector);
}

t_vector	my_normal(t_vector not_norm_vector)
{
	t_vector	norm_vector;
	double		len_vector;

	len_vector = my_lenght_vector(not_norm_vector);
	norm_vector.x = not_norm_vector.x / len_vector;
	norm_vector.y = not_norm_vector.y / len_vector;
	norm_vector.z = not_norm_vector.z / len_vector;
	return (norm_vector);
}

t_vector	my_cross_prod(t_vector vector1, t_vector vector2)
{
	t_vector cross_vector;

	cross_vector.x = vector1.y * vector2.z - vector1.z * vector2.y;
	cross_vector.y = vector1.z * vector2.x - vector1.x * vector2.z;
	cross_vector.z = vector1.x * vector2.y - vector1.y * vector2.x;
	return (cross_vector);
}

double		my_dot_prod(t_vector v1, t_vector v2)
{
	return (v1.x * v2.x + v1.y * v2.y + v1.z * v2.z);
}

t_vector	my_negative(t_vector vector)
{
	t_vector neg_vector;

	neg_vector.x = -vector.x;
	neg_vector.y = -vector.y;
	neg_vector.z = -vector.z;
	return (neg_vector);
}
