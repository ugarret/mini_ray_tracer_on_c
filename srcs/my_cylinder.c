#include "../includes/rtmini.h"

void			set_param_cylinder(char **arr, t_scene *scene)
{
	t_cylinder *n_cld;

	if (arr[12] == 0)
	{
		if (!(n_cld = (t_cylinder *)my_calloc(1, sizeof(t_cylinder))))
			my_error("Memory allocation error");
		my_set_coords(&n_cld->center, my_atof(arr[1]), my_atof(arr[2]),
			my_atof(arr[3]));
		n_cld->norm_vector.x = check_norm_coords(my_atof(arr[4]));
		n_cld->norm_vector.y = check_norm_coords(my_atof(arr[5]));
		n_cld->norm_vector.z = check_norm_coords(my_atof(arr[6]));
		n_cld->norm_vector = my_normal(n_cld->norm_vector);
		if ((n_cld->diameter = my_atof(arr[7])) <= 1e-5)
			my_error("The value is less than acceptable for diameter\n");
		if ((n_cld->height = my_atof(arr[8])) <= 1e-5)
			my_error("The value is less than acceptable for height\n");
		my_set_and_check_color(&n_cld->color.x, my_atoi(arr[9]) / (double)255);
		my_set_and_check_color(&n_cld->color.y, my_atoi(arr[10]) / (double)255);
		my_set_and_check_color(&n_cld->color.z, my_atoi(arr[11]) / (double)255);
		my_add_back(&scene->cld, my_list_new(n_cld));
	}
	else
		my_error("Incorrect number of parametrs\n");
}

static double	p_by_height(t_impact_p *i, t_cylinder *cy, double x1, double x2)
{
	double		dot;
	double		tmp;

	if (x1 > x2)
	{
		tmp = x1;
		x1 = x2;
		x2 = tmp;
	}
	dot = my_dot_prod(cy->norm_vector, my_sub(my_add(i->cam_point,
		my_mylt_num(i->ray_dir, x1)), cy->center));
	if (x1 < 0 || (dot < 0 || dot > cy->height))
	{
		x1 = x2;
		dot = my_dot_prod(cy->norm_vector, my_sub(my_add(i->cam_point,
			my_mylt_num(i->ray_dir, x1)), cy->center));
		if (x1 < 0 || (dot < 0 || dot > cy->height))
			x1 = INFINITY;
	}
	return (x1);
}

static double	points_inter_cylinder(t_impact_p *impact, t_cylinder *cylinder)
{
	t_vector	oc;
	t_vector	coef;
	double		x1;
	double		x2;
	double		tmp;

	oc = my_sub(impact->cam_point, cylinder->center);
	tmp = my_dot_prod(impact->ray_dir, cylinder->norm_vector);
	coef.x = my_dot_prod(impact->ray_dir, impact->ray_dir) - pow(tmp, 2);
	tmp = tmp * my_dot_prod(oc, cylinder->norm_vector);
	coef.y = 2 * (my_dot_prod(impact->ray_dir, oc) - tmp);
	tmp = my_dot_prod(oc, cylinder->norm_vector);
	coef.z = my_dot_prod(oc, oc) - pow(tmp, 2) - (pow(cylinder->diameter,
		2) / 4);
	if ((coef.y * coef.y - 4 * coef.z * coef.x) < 0)
		return (INFINITY);
	if ((x1 = -(coef.y + sqrt(coef.y * coef.y - 4 * coef.z * coef.x)) /
		(2 * coef.x)) < 0)
		x1 = INFINITY;
	if ((x2 = -(coef.y - sqrt(coef.y * coef.y - 4 * coef.z * coef.x)) /
		(2 * coef.x)) < 0)
		x2 = INFINITY;
	return (p_by_height(impact, cylinder, x1, x2));
}

void			my_trace_cylinder(t_impact_p *imp, t_list *list_of_cylinder)
{
	double		closest_p;
	t_cylinder	*cy;
	double		t;
	t_vector	v;

	t = INFINITY;
	closest_p = imp->t;
	while (list_of_cylinder)
	{
		cy = (t_cylinder *)list_of_cylinder->content;
		if ((t = points_inter_cylinder(imp, cy)) < closest_p)
		{
			imp->color = cy->color;
			closest_p = t;
			imp->point_impact = my_add(imp->cam_point, my_mylt_num(imp->ray_dir, closest_p));
			v = my_sub(imp->point_impact, cy->center);
			imp->norm_v_impact = my_normal(my_sub(v, my_mylt_num(cy->norm_vector, my_dot_prod(v, cy->norm_vector))));
			imp->norm_v_impact = my_normal(my_mylt_num(imp->norm_v_impact, my_dot_prod(imp->norm_v_impact, my_negative(imp->ray_dir))));
			imp->t = closest_p;
		}
		list_of_cylinder = list_of_cylinder->next;
	}
}
