#include "../includes/rtmini.h"

double	check_norm_coords(double num)
{
	if (num > 1 + 1e-5)
		my_error("The value is more than acceptable for normal");
	else if (num < -1 - 1e-5)
		my_error("The value is less than acceptable for normal");
	return (num);
}

void	my_set_coords(t_vector *coord, double x, double y, double z)
{
	coord->x = x;
	coord->y = y;
	coord->z = z;
}

int		my_set_and_check_color(double *color, double x)
{
	if (x > 1)
		my_error("The value is more than acceptable for color");
	else if (x < 0)
		my_error("The value is less than acceptable for color");
	else
		*color = x;
	return (0);
}

void	set_param_camera(char **arr, t_scene *scene)
{
	t_camera	*new_cam;

	if (arr[8] == 0)
	{
		if (!(new_cam = (t_camera *)my_calloc(1, sizeof(t_camera))))
			my_error("Memory allocation error");
		my_set_coords(&new_cam->center, my_atof(arr[1]), my_atof(arr[2]),
			my_atof(arr[3]));
		new_cam->norm_vector.x = check_norm_coords(my_atof(arr[4]));
		new_cam->norm_vector.y = check_norm_coords(my_atof(arr[5]));
		new_cam->norm_vector.z = check_norm_coords(my_atof(arr[6]));
		if ((new_cam->fov = my_atof(arr[7])) > 180 || new_cam->fov < 0)
			my_error("The incorrect value for fov");
		my_add_back(&scene->cam, my_list_new(new_cam));
	}
	else
		my_error("Incorrect number of parametrs\n");
}

void	set_param_light(char **arr, t_scene *scene)
{
	t_light	*n_lgh;

	if (arr[8] == 0)
	{
		if (!(n_lgh = (t_light *)my_calloc(1, sizeof(t_light))))
			my_error("Memory allocation error");
		my_set_coords(&n_lgh->center, my_atof(arr[1]), my_atof(arr[2]),
			my_atof(arr[3]));
		if ((n_lgh->bright = my_atof(arr[4])) < 0)
			my_error("The value is less than acceptable for bright");
		my_set_and_check_color(&n_lgh->color_light.x, my_atoi(arr[5]) /
			(double)255);
		my_set_and_check_color(&n_lgh->color_light.y, my_atoi(arr[6]) /
			(double)255);
		my_set_and_check_color(&n_lgh->color_light.z, my_atoi(arr[7]) /
			(double)255);
		my_add_back(&scene->lgh, my_list_new(n_lgh));
	}
	else
		my_error("Incorrect number of parametrs\n");
}
