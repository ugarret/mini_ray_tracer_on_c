#include "../includes/rtmini.h"

void			set_param_triangle(char **arr, t_scene *scene)
{
	t_triangle	*n_trg;

	if (arr[13] == 0)
	{
		if (!(n_trg = (t_triangle *)my_calloc(1, sizeof(t_triangle))))
			my_error("Memory allocation error");
		my_set_coords(&n_trg->fst_point, my_atof(arr[1]), my_atof(arr[2]),
			my_atof(arr[3]));
		my_set_coords(&n_trg->snd_point, my_atof(arr[4]), my_atof(arr[5]),
			my_atof(arr[6]));
		my_set_coords(&n_trg->trd_point, my_atof(arr[7]), my_atof(arr[8]),
			my_atof(arr[9]));
		my_set_and_check_color(&n_trg->color.x, my_atoi(arr[10]) / (double)255);
		my_set_and_check_color(&n_trg->color.y, my_atoi(arr[11]) / (double)255);
		my_set_and_check_color(&n_trg->color.z, my_atoi(arr[12]) / (double)255);
		my_add_back(&scene->trg, my_list_new(n_trg));
	}
	else
		my_error("Incorrect number of parametrs\n");
}

static double	points_inter_triangle(t_triangle *triangle, t_impact_p *impact)
{
	t_vector	snd_fst;
	t_vector	trd_fst;
	double		determinant;
	t_solution	solution;

	snd_fst = my_sub(triangle->snd_point, triangle->fst_point);
	trd_fst = my_sub(triangle->trd_point, triangle->fst_point);
	solution.cross_dir_3_1 = my_cross_prod(impact->ray_dir, trd_fst);
	determinant = my_dot_prod(snd_fst, solution.cross_dir_3_1);
	if (fabs(determinant) < 1e-8)
		return (INFINITY);
	solution.fst_cam = my_sub(impact->cam_point, triangle->fst_point);
	solution.u = my_dot_prod(solution.fst_cam, solution.cross_dir_3_1)
		* (1.0 / determinant);
	if (solution.u < 0.0 || solution.u > 1)
		return (INFINITY);
	solution.cross_1_cam_2_1 = my_cross_prod(solution.fst_cam, snd_fst);
	solution.v = my_dot_prod(impact->ray_dir, solution.cross_1_cam_2_1)
		* (1.0 / determinant);
	if (solution.v < 0.0 || solution.u + solution.v > 1)
		return (INFINITY);
	triangle->norm_vector = my_normal(my_cross_prod(trd_fst, snd_fst));
	return (my_dot_prod(trd_fst, solution.cross_1_cam_2_1)
		* (1.0 / determinant));
}

void			my_trace_triangle(t_impact_p *impact, t_list *list_of_triangle)
{
	double		closest_p;
	t_triangle	*tr;
	double		t;

	closest_p = impact->t;
	while (list_of_triangle)
	{
		tr = (t_triangle *)list_of_triangle->content;
		t = points_inter_triangle(tr, impact);
		if (t < closest_p && t > 0)
		{
			impact->color = tr->color;
			closest_p = t;
			impact->point_impact = my_add(impact->cam_point,
				my_mylt_num(impact->ray_dir, closest_p));
			impact->norm_v_impact = my_normal(my_mylt_num(tr->norm_vector,
				my_dot_prod(tr->norm_vector, my_negative(impact->ray_dir))));
			impact->point_impact = my_add(impact->point_impact,
				my_mylt_num(impact->norm_v_impact, 1e-3));
			impact->t = closest_p;
		}
		list_of_triangle = list_of_triangle->next;
	}
}
