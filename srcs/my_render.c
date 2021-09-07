#include "../includes/rtmini.h"

static int	create_trgb(int t, int r, int g, int b)
{
	return ((t << 24) | (r << 16) | (g << 8) | b);
}

static void	my_mlx_pixel_put(t_for_mlx *data, int x, int y, int color)
{
	char	*dst;

	dst = data->addr + (y * data->line_length + x * (data->bits_per_pixel / 8));
	*(unsigned int*)dst = color;
}

static void	my_ray_trace(t_impact_p *impact, t_scene *scene)
{
	impact->t = INFINITY;
	my_bzero(&impact->color, sizeof(t_vector));
	if (scene->sph != NULL)
		my_trace_sphere(impact, scene->sph);
	if (scene->pln != NULL)
		my_trace_plane(impact, scene->pln);
	if (scene->trg != NULL)
		my_trace_triangle(impact, scene->trg);
	if (scene->squ != NULL)
		my_trace_square(impact, scene->squ, INFINITY);
	if (scene->cld != NULL)
		my_trace_cylinder(impact, scene->cld);
	my_dark_or_light(impact, scene);
	impact->color.x = (impact->color.x > 1) ? 1 : impact->color.x;
	impact->color.y = (impact->color.y > 1) ? 1 : impact->color.y;
	impact->color.z = (impact->color.z > 1) ? 1 : impact->color.z;
	impact->res_color = create_trgb(0, impact->color.x * 255,
		impact->color.y * 255, impact->color.z * 255);
}

void		my_render(t_scene *scene, t_for_mlx *vars)
{
	int			i;
	int			j;
	double		caliber;
	t_vector	ray;
	t_impact_p	impact;

	j = -1;
	vars->eye = (t_camera *)scene->cam->content;
	my_matrix_for_new_camera(vars);
	caliber = tan((vars->eye->fov / 2.0) * (M_PI / 180));
	impact.cam_point = vars->eye->center;
	impact.res_color = 0;
	while (++j < scene->m_p.y)
	{
		i = 0;
		while (++i < scene->m_p.x)
		{
			ray.x = (2.0 * i + 1.0 - scene->m_p.x) / scene->m_p.y * caliber;
			ray.y = (1.0 - (2.0 * j + 1.0) / scene->m_p.y) * caliber;
			ray.z = -1;
			impact.ray_dir = my_normal(my_mult_matrix_vec(vars->matrix, ray));
			my_ray_trace(&impact, scene);
			my_mlx_pixel_put(vars, i, j, impact.res_color);
		}
	}
}
