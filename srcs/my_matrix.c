#include "../includes/rtmini.h"

t_vector	my_mult_matrix_vec(double m[4][4], t_vector v)
{
	return (my_new_vector(m[0][0] * v.x + m[1][0] * v.y + m[2][0] * v.z,
						m[0][1] * v.x + m[1][1] * v.y + m[2][1] * v.z,
						m[0][2] * v.x + m[1][2] * v.y + m[2][2] * v.z));
}

void		my_full_matrix(double matrix_4_by_4[4][4])
{
	matrix_4_by_4[0][3] = 0;
	matrix_4_by_4[1][3] = 0;
	matrix_4_by_4[2][3] = 0;
	matrix_4_by_4[3][3] = 1;
}

void		my_matrix_for_new_camera(t_for_mlx *vars)
{
	t_vector	axis_x;
	t_vector	axis_y;
	t_vector	axis_z;

	axis_z = my_normal(my_negative(vars->eye->norm_vector));
	axis_x = my_normal(my_cross_prod(my_new_vector(0, 2, 0), axis_z));
	axis_y = my_normal(my_cross_prod(axis_z, axis_x));
	vars->matrix[0][0] = axis_x.x;
	vars->matrix[0][1] = axis_x.y;
	vars->matrix[0][2] = axis_x.z;
	vars->matrix[1][0] = axis_y.x;
	vars->matrix[1][1] = axis_y.y;
	vars->matrix[1][2] = axis_y.z;
	vars->matrix[2][0] = axis_z.x;
	vars->matrix[2][1] = axis_z.y;
	vars->matrix[2][2] = axis_z.z;
	vars->matrix[3][0] = vars->eye->center.x;
	vars->matrix[3][1] = vars->eye->center.y;
	vars->matrix[3][2] = vars->eye->center.z;
	my_full_matrix(vars->matrix);
}
