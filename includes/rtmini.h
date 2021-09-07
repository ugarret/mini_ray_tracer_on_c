#ifndef RTMINI_H
# define RTMINI_H

# include <fcntl.h>
# include <stdio.h>
# include <stdlib.h>
# include <math.h>
# include "../includes/mylib.h"
# include "../minilibx_mms/mlx.h"

typedef struct		s_vector
{
	double			x;
	double			y;
	double			z;
}					t_vector;

typedef struct
{
	int				x;
	int				y;
	double			light_ratio;
	t_vector		amb_light_color;
	int				counter_r;
	int				counter_a;
}					t_param;

typedef struct		s_camera
{
	t_vector		center;
	t_vector		norm_vector;
	double			fov;
}					t_camera;

typedef struct		s_light
{
	t_vector		center;
	double			bright;
	t_vector		color_light;
}					t_light;

typedef struct		s_sphere
{
	t_vector		center;
	double			diameter;
	t_vector		color;
}					t_sphere;

typedef struct		s_plane
{
	t_vector		center;
	t_vector		norm_vector;
	t_vector		color;
}					t_plane;

typedef struct		s_square
{
	t_vector		center;
	t_vector		norm_vector;
	double			side_size;
	t_vector		color;
}					t_square;

typedef struct		s_cylinder
{
	t_vector		center;
	t_vector		norm_vector;
	double			diameter;
	double			height;
	t_vector		color;
}					t_cylinder;

typedef struct		s_triangle
{
	t_vector		fst_point;
	t_vector		snd_point;
	t_vector		trd_point;
	t_vector		color;
	t_vector		norm_vector;
}					t_triangle;

typedef struct		s_list
{
	void			*content;
	struct s_list	*next;
}					t_list;

typedef struct		s_impact_p
{
	t_vector		cam_point;
	t_vector		ray_dir;
	t_vector		point_impact;
	t_vector		norm_v_impact;
	t_vector		color;
	int				res_color;
	double			t;
}					t_impact_p;

typedef struct		s_for_mlx
{
	void			*mlx;
	void			*win;
	void			*img;
	char			*addr;
	int				bits_per_pixel;
	int				line_length;
	int				endian;
	t_camera		*eye;
	double			matrix[4][4];
}					t_for_mlx;

typedef struct		s_solution
{
	t_vector		cross_dir_3_1;
	t_vector		fst_cam;
	t_vector		cross_1_cam_2_1;
	double			u;
	double			v;
}					t_solution;

typedef struct		s_ray_light
{
	t_vector		ambient;
	t_vector		diffuse;
	t_vector		specular;
	t_vector		total;
}					t_l;

typedef struct		s_scene
{
	t_param			m_p;
	t_list			*cam;
	t_list			*lgh;
	t_list			*sph;
	t_list			*pln;
	t_list			*squ;
	t_list			*cld;
	t_list			*trg;
	t_for_mlx		*for_mlx;
	int				nmb_arg;
}					t_scene;

void				set_param_resol(char **arr, t_scene *scene);
void				set_param_amb_light(char **arr, t_scene *scene);
int					my_add_back(t_list **list, t_list *new);
void				set_param_camera(char **arr, t_scene *scene);
void				set_param_light(char **arr, t_scene *scene);
void				set_param_sphere(char **arr, t_scene *scene);
void				set_param_plane(char **arr, t_scene *scene);
void				set_param_square(char **arr, t_scene *scene);
void				set_param_cylinder(char **arr, t_scene *scene);
void				set_param_triangle(char **arr, t_scene *scene);
void				my_parsing_file(int fd, t_scene *scene);
t_list				*my_list_new(void *content);
t_vector			my_new_vector(double x, double y, double z);
t_vector			my_normal(t_vector not_norm_vector);
t_vector			my_cross_prod(t_vector vector1, t_vector vector2);
double				my_dot_prod(t_vector v1, t_vector v2);
t_vector			my_negative(t_vector vector);
t_vector			my_add(t_vector v1, t_vector v2);
t_vector			my_sub(t_vector v1, t_vector v2);
t_vector			my_mylt_num(t_vector v, double num);
double				my_lenght_vector(t_vector v);
t_vector			my_mult_two_vectors(t_vector v1, t_vector v2);
t_vector			my_mult_matrix_vec(double m[4][4], t_vector v);
void				my_full_matrix(double matrix_4_by_4[4][4]);
void				my_matrix_for_new_camera(t_for_mlx *vars);
void				my_trace_sphere(t_impact_p *impact, t_list *list_of_sphere);
void				my_trace_plane(t_impact_p *impact, t_list *list_of_plane);
void				my_trace_triangle(t_impact_p *impact, t_list *l_of_tr);
void				my_set_coords(t_vector *co, double x, double y, double z);
int					my_set_and_check_color(double *color, double x);
double				check_norm_coords(double num);
void				my_trace_cylinder(t_impact_p *impact, t_list *l_of_cl);
void				my_trace_square(t_impact_p *im, t_list *l_of_sq, double t);
void				my_save_bmp(t_scene *scene, t_for_mlx *vars);
void				my_error(char *message);
void				my_render(t_scene *scene, t_for_mlx *vars);
void				my_dark_or_light(t_impact_p *impact, t_scene *scene);

#endif
