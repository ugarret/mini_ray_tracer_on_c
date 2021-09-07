#include "../includes/rtmini.h"

static void	my_free_arr(char **arr)
{
	unsigned int	i;

	i = 0;
	while (arr[i])
	{
		free(arr[i]);
		i++;
	}
	free(arr);
	arr = NULL;
}

static void	my_parsing_line(char **arr, t_scene *scene)
{
	if (my_strncmp(arr[0], "R", 1) == 0)
		set_param_resol(arr, scene);
	else if (my_strncmp(arr[0], "A", 1) == 0)
		set_param_amb_light(arr, scene);
	else if (my_strncmp(arr[0], "c", 2) == 0)
		set_param_camera(arr, scene);
	else if (my_strncmp(arr[0], "l", 2) == 0)
		set_param_light(arr, scene);
	else if (my_strncmp(arr[0], "sp", 2) == 0)
		set_param_sphere(arr, scene);
	else if (my_strncmp(arr[0], "pl", 2) == 0)
		set_param_plane(arr, scene);
	else if (my_strncmp(arr[0], "sq", 2) == 0)
		set_param_square(arr, scene);
	else if (my_strncmp(arr[0], "cy", 2) == 0)
		set_param_cylinder(arr, scene);
	else if (my_strncmp(arr[0], "tr", 2) == 0)
		set_param_triangle(arr, scene);
	else
		my_error("There is no a figure\n");
}

void		my_parsing_file(int fd, t_scene *scene)
{
	char		*line;
	int			ending;
	int			res_gnl;
	char		**arr;
	int			flag;

	ending = 0;
	flag = 0;
	while (!ending && (res_gnl = get_line_from_file(fd, &line)) >= 0)
	{
		(res_gnl == 0) ? ending++ : ending;
		if (line[0] == ' ')
			flag = 1;
		line = my_skip_space(line);
		if ((line[0] != '\0' || line[0] != '\n') && flag)
			my_error("There is no a figure\n");
		arr = my_split(line);
		if (arr != NULL && arr[0] != NULL && arr[0][0] != '\0')
			my_parsing_line(arr, scene);
		my_free_arr(arr);
		free(line);
	}
	if (res_gnl == -1)
		my_error("Error reading from scene file\n");
	if (scene->m_p.counter_r != 1 || scene->m_p.counter_a != 1)
		my_error("There is no main parameters\n");
	if (scene->cam != NULL)
		my_add_back(&scene->cam, scene->cam);
	else
		my_error("There is no camera, add one\n");
}

void		set_param_resol(char **arr, t_scene *scene)
{
	int	size_x;
	int	size_y;

	if (arr[3] == 0)
	{
		scene->m_p.counter_r++;
		scene->for_mlx->mlx = mlx_init();
		mlx_get_screen_size(scene->for_mlx->mlx, &size_x, &size_y);
		scene->m_p.x = my_atoi(arr[1]);
		if (scene->m_p.x > size_x && scene->nmb_arg == 2)
			scene->m_p.x = size_x;
		scene->m_p.y = my_atoi(arr[2]);
		if (scene->m_p.y > size_y && scene->nmb_arg == 2)
			scene->m_p.y = size_y;
		if (scene->m_p.x < 1 || scene->m_p.y < 1)
			my_error("Invalid resolution\n");
		if (scene->m_p.counter_r > 1)
			my_error("Parameter occurs more than two times\n");
	}
	else
		my_error("Incorrect number of parametrs\n");
}

void		set_param_amb_light(char **arr, t_scene *scene)
{
	if (arr[5] == 0)
	{
		scene->m_p.counter_a++;
		if ((scene->m_p.light_ratio = my_atof(arr[1])) < 0)
			my_error("The value is less than acceptable for light ratio\n");
		my_set_and_check_color(&scene->m_p.amb_light_color.x,
			my_atoi(arr[2]) / (double)255);
		my_set_and_check_color(&scene->m_p.amb_light_color.y,
			my_atoi(arr[3]) / (double)255);
		my_set_and_check_color(&scene->m_p.amb_light_color.z,
			my_atoi(arr[4]) / (double)255);
		if (scene->m_p.counter_a > 1)
			my_error("Parameter occurs more than two times\n");
	}
	else
		my_error("Incorrect number of parametrs\n");
}
