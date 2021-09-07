#include "../includes/rtmini.h"

static int	close_with_cross(void)
{
	exit(0);
	return (0);
}

static int	key_hook(int keycode, t_scene *scene)
{
	if (keycode == 36)
	{
		scene->cam = scene->cam->next;
		scene->for_mlx->eye = (t_camera *)scene->cam->content;
		write(1, "camera changing...\n", 19);
		my_render(scene, scene->for_mlx);
		mlx_put_image_to_window(scene->for_mlx->mlx, scene->for_mlx->win,
			scene->for_mlx->img, 0, 0);
	}
	if (keycode == 53)
	{
		exit(0);
	}
	return (0);
}

static int	my_check_argc_argv(int argc, char **argv)
{
	int i;

	if (argc < 2 || argc > 3)
		my_error("Wrong number of argv\n");
	if (argc == 3)
	{
		if (my_strncmp("--save", argv[2], 7))
			my_error("Unknown flag, use --save\n");
		return (3);
	}
	else
	{
		i = 0;
		while (argv[1][i] != '.')
			i++;
		if (i == 0 || !(my_strncmp(".rt", argv[2], 4)))
			my_error("Unknown file\n");
	}
	return (2);
}

void		my_all_for_mlx(t_scene *scene)
{
	scene->for_mlx->eye = (t_camera *)scene->cam->content;
	scene->for_mlx->img = mlx_new_image(scene->for_mlx->mlx,
		scene->m_p.x, scene->m_p.y);
	scene->for_mlx->addr = mlx_get_data_addr(scene->for_mlx->img,
		&scene->for_mlx->bits_per_pixel, &scene->for_mlx->line_length,
		&scene->for_mlx->endian);
}

int			main(int argc, char **argv)
{
	int			fd;
	t_scene		*scene;

	scene = (t_scene *)my_calloc(1, sizeof(t_scene));
	scene->for_mlx = (t_for_mlx *)calloc(1, sizeof(t_for_mlx));
	scene->nmb_arg = my_check_argc_argv(argc, argv);
	if ((fd = open(argv[1], O_RDONLY)) == -1)
		my_error("Fail to open the file\n");
	my_parsing_file(fd, scene);
	close(fd);
	my_all_for_mlx(scene);
	my_render(scene, scene->for_mlx);
	if (scene->nmb_arg == 3)
		my_save_bmp(scene, scene->for_mlx);
	else
	{
		scene->for_mlx->win = mlx_new_window(scene->for_mlx->mlx, scene->m_p.x,
			scene->m_p.y, "Just trust me, my miniRT is good boy");
		mlx_put_image_to_window(scene->for_mlx->mlx, scene->for_mlx->win,
			scene->for_mlx->img, 0, 0);
		mlx_hook(scene->for_mlx->win, 2, 1L << 0, key_hook, scene);
		mlx_hook(scene->for_mlx->win, 17, 1L << 0, close_with_cross, scene);
		mlx_loop(scene->for_mlx->mlx);
	}
	return (0);
}
