#include "../includes/rtmini.h"

void	set_param_plane(char **arr, t_scene *scene)
{
	t_plane *n_pln;

	if (arr[10] == 0)
	{
		if (!(n_pln = (t_plane *)my_calloc(1, sizeof(t_plane))))
			my_error("Memory allocation error");
		my_set_coords(&n_pln->center, my_atof(arr[1]), my_atof(arr[2]),
			my_atof(arr[3]));
		n_pln->norm_vector.x = check_norm_coords(my_atof(arr[4]));
		n_pln->norm_vector.y = check_norm_coords(my_atof(arr[5]));
		n_pln->norm_vector.z = check_norm_coords(my_atof(arr[6]));
		n_pln->norm_vector = my_normal(n_pln->norm_vector);
		my_set_and_check_color(&n_pln->color.x, my_atoi(arr[7]) / (double)255);
		my_set_and_check_color(&n_pln->color.y, my_atoi(arr[8]) / (double)255);
		my_set_and_check_color(&n_pln->color.z, my_atoi(arr[9]) / (double)255);
		my_add_back(&scene->pln, my_list_new(n_pln));
	}
	else
		my_error("Incorrect number of parametrs\n");
}

void	my_trace_plane(t_impact_p *imp, t_list *list_of_plane)
{
	double		closest_p;
	t_plane		*pl;
	double		t;

	t = INFINITY;
	closest_p = imp->t;
	while (list_of_plane)
	{
		pl = (t_plane *)list_of_plane->content;
		if ((fabs(my_dot_prod(imp->ray_dir, pl->norm_vector))) > 0.0)
			t = my_dot_prod(my_sub(pl->center, imp->cam_point),
				pl->norm_vector) / my_dot_prod(imp->ray_dir, pl->norm_vector);
		if (t < closest_p && t > 0)
		{
			imp->color = pl->color;
			closest_p = t;
			imp->point_impact = my_add(imp->cam_point,
				my_mylt_num(imp->ray_dir, closest_p));
			imp->norm_v_impact = my_normal(my_mylt_num(pl->norm_vector,
				my_dot_prod(pl->norm_vector, my_negative(imp->ray_dir))));
			imp->t = closest_p;
		}
		list_of_plane = list_of_plane->next;
	}
}
