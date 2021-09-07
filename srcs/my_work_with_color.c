#include "../includes/rtmini.h"

static int	in_shadow(t_light *light, t_scene *scene, t_impact_p *impact)
{
	t_impact_p	light_impact;
	double		distance;

	light_impact.t = INFINITY;
	light_impact.ray_dir = my_sub(my_add(impact->point_impact,
		my_mylt_num(impact->norm_v_impact, 0.00001)), light->center);
	distance = my_lenght_vector(light_impact.ray_dir);
	light_impact.ray_dir = my_normal(light_impact.ray_dir);
	light_impact.cam_point = light->center;
	my_trace_sphere(&light_impact, scene->sph);
	if (light_impact.t != INFINITY && distance > light_impact.t)
		return (1);
	my_trace_plane(&light_impact, scene->pln);
	if (light_impact.t != INFINITY && distance > light_impact.t)
		return (1);
	my_trace_square(&light_impact, scene->squ, INFINITY);
	if (light_impact.t != INFINITY && distance > light_impact.t)
		return (1);
	my_trace_triangle(&light_impact, scene->trg);
	if (light_impact.t != INFINITY && distance > light_impact.t)
		return (1);
	my_trace_cylinder(&light_impact, scene->cld);
	if (light_impact.t != INFINITY && distance > light_impact.t)
		return (1);
	return (0);
}

static void	my_d_and_s(t_l *l_ray, t_light *lg, t_impact_p *imp, t_vector l_v)
{
	double		q;
	t_vector	reflect_dir;
	double		spec;

	q = fmax(my_dot_prod(imp->norm_v_impact, l_v), 0.0);
	l_ray->diffuse = my_add(l_ray->diffuse, my_mylt_num(lg->color_light, q));
	reflect_dir = my_sub(l_v, my_mylt_num(imp->norm_v_impact,
	my_dot_prod(l_v, imp->norm_v_impact) * 2));
	spec = pow(fmax(my_dot_prod(imp->ray_dir, reflect_dir), 0.0), 32);
	l_ray->specular = my_add(l_ray->specular, my_mylt_num(lg->color_light,
		lg->bright * spec));
}

void		my_dark_or_light(t_impact_p *impact, t_scene *scene)
{
	t_l			*l_ray;
	t_vector	light_vector;
	t_light		*light;
	t_list		*list_of_light;

	l_ray = (t_l *)my_calloc(1, sizeof(t_l));
	l_ray->ambient = my_mylt_num(scene->m_p.amb_light_color,
		scene->m_p.light_ratio);
	list_of_light = scene->lgh;
	while (list_of_light != NULL)
	{
		light = (t_light *)list_of_light->content;
		light_vector = my_normal(my_sub(light->center, impact->point_impact));
		if (!signbit(my_dot_prod(impact->norm_v_impact, light_vector)))
			if (!in_shadow(light, scene, impact))
				my_d_and_s(l_ray, light, impact, light_vector);
		list_of_light = list_of_light->next;
	}
	impact->color = my_mult_two_vectors(impact->color,
		my_add(my_add(l_ray->ambient, l_ray->diffuse), l_ray->specular));
	free(l_ray);
}
