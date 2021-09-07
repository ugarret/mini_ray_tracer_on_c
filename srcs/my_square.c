#include "../includes/rtmini.h"

void			set_param_square(char **arr, t_scene *scene)
{
	t_square *n_squ;

	if (arr[11] == 0)
	{
		if (!(n_squ = (t_square *)my_calloc(1, sizeof(t_square))))
			my_error("Memory allocation error");
		my_set_coords(&n_squ->center, my_atof(arr[1]), my_atof(arr[2]),
			my_atof(arr[3]));
		n_squ->norm_vector.x = check_norm_coords(my_atof(arr[4]));
		n_squ->norm_vector.y = check_norm_coords(my_atof(arr[5]));
		n_squ->norm_vector.z = check_norm_coords(my_atof(arr[6]));
		n_squ->norm_vector = my_normal(n_squ->norm_vector);
		if ((n_squ->side_size = my_atof(arr[7])) <= 1e-5)
			printf("The value is less than acceptable for side size");
		my_set_and_check_color(&n_squ->color.x, my_atoi(arr[8]) / (double)255);
		my_set_and_check_color(&n_squ->color.y, my_atoi(arr[9]) / (double)255);
		my_set_and_check_color(&n_squ->color.z, my_atoi(arr[10]) / (double)255);
		my_add_back(&scene->squ, my_list_new(n_squ));
	}
	else
		my_error("Incorrect number of parametrs\n");
}

static double	point_inter_square(t_impact_p *imp, t_square *sq, double t)
{
	t_vector	l_x;
	t_vector	l_y;
	t_vector	l_z;
	t_vector	p;

	t = my_dot_prod(my_sub(sq->center, imp->cam_point),
	sq->norm_vector) / my_dot_prod(sq->norm_vector, imp->ray_dir);
	if (t > 1e-7)
	{
		l_z = sq->norm_vector;
		l_x = my_cross_prod(my_new_vector(0, 1, 0), l_z);
		if (fabs(l_x.x) < 1e-7 && fabs(l_x.y) < 1e-7 && fabs(l_x.z) < 1e-7)
			l_x = my_cross_prod(my_new_vector(0, 0, 1), l_z);
		l_x = my_normal(l_x);
		l_y = my_normal(my_cross_prod(l_z, l_x));
		p = my_sub(my_add(imp->cam_point, my_mylt_num(imp->ray_dir, t)),
			sq->center);
		if (fabs(my_dot_prod(l_y, p)) <= sq->side_size / 2)
			if (fabs(my_dot_prod(l_x, p)) <= sq->side_size / 2)
				return (t);
	}
	return (INFINITY);
}

void			my_trace_square(t_impact_p *imp, t_list *list_of_sq, double t)
{
	double		cl;
	t_square	*sq;

	cl = imp->t;
	while (list_of_sq)
	{
		sq = (t_square *)list_of_sq->content;
		sq->norm_vector = my_normal(sq->norm_vector);
		if (fabs(my_dot_prod(sq->norm_vector, imp->ray_dir)) > 1e-7)
			t = point_inter_square(imp, sq, t);
		if (t < cl && t > 0)
		{
			imp->color = sq->color;
			cl = t;
			imp->point_impact = my_add(imp->cam_point,
				my_mylt_num(imp->ray_dir, cl));
			imp->norm_v_impact = my_normal(my_mylt_num(sq->norm_vector,
				my_dot_prod(sq->norm_vector, my_negative(imp->ray_dir))));
			imp->point_impact = my_add(imp->point_impact,
				my_mylt_num(imp->norm_v_impact, 1e-3));
			imp->t = cl;
		}
		list_of_sq = list_of_sq->next;
	}
}
