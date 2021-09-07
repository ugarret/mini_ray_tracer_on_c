#include "../includes/rtmini.h"

void			set_param_sphere(char **arr, t_scene *scene)
{
	t_sphere	*n_sph;

	if (arr[8] == 0)
	{
		if (!(n_sph = (t_sphere *)my_calloc(1, sizeof(t_sphere))))
			my_error("Memory allocation error");
		my_set_coords(&n_sph->center, my_atof(arr[1]), my_atof(arr[2]),
			my_atof(arr[3]));
		if ((n_sph->diameter = my_atof(arr[4])) <= 1e-7)
			my_error("The value is less than acceptable for diameter");
		my_set_and_check_color(&n_sph->color.x, my_atoi(arr[5]) / (double)255);
		my_set_and_check_color(&n_sph->color.y, my_atoi(arr[6]) / (double)255);
		my_set_and_check_color(&n_sph->color.z, my_atoi(arr[7]) / (double)255);
		my_add_back(&scene->sph, my_list_new(n_sph));
	}
	else
		my_error("Incorrect number of parametrs\n");
}

static double	points_inter_sphere(t_impact_p *imp, t_sphere *sp, double close)
{
	t_vector	v_centr_camera;
	double		b;
	double		c;
	double		x1;
	double		x2;

	v_centr_camera = my_sub(imp->cam_point, sp->center);
	b = 2 * my_dot_prod(v_centr_camera, imp->ray_dir);
	c = my_dot_prod(v_centr_camera, v_centr_camera) -
		pow(sp->diameter / 2, 2);
	if ((b * b - 4 * c) < 0)
		return (INFINITY);
	if ((x1 = -(b + sqrt(b * b - 4 * c)) / 2) < 0.0000001)
		x1 = INFINITY;
	if ((x2 = -(b - sqrt(b * b - 4 * c)) / 2) < 0.0000001)
		x2 = INFINITY;
	if (x1 < x2)
		x2 = x1;
	if (x2 < close)
		close = x2;
	return (close);
}

void			my_trace_sphere(t_impact_p *imp, t_list *list_of_sphere)
{
	double		closest_p;
	t_sphere	*sphere;
	double		t;

	t = INFINITY;
	closest_p = imp->t;
	while (list_of_sphere)
	{
		sphere = (t_sphere *)list_of_sphere->content;
		if ((t = points_inter_sphere(imp, sphere, closest_p)) < closest_p)
		{
			imp->color = sphere->color;
			closest_p = t;
			imp->point_impact = my_add(imp->cam_point, my_mylt_num(imp->ray_dir, closest_p));
			imp->norm_v_impact = my_normal(my_sub(imp->point_impact, sphere->center));
			imp->norm_v_impact = my_normal(my_mylt_num(imp->norm_v_impact, my_dot_prod(imp->norm_v_impact, my_negative(imp->ray_dir))));
			imp->point_impact = my_add(imp->point_impact, my_mylt_num(imp->norm_v_impact, 1e-3));
			imp->t = closest_p;
		}
		list_of_sphere = list_of_sphere->next;
	}
}
