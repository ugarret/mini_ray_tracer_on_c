#include "../includes/rtmini.h"

#define HEADER_SIZE 14
#define INFO_SIZE 40
#define X scene->m_p.x
#define Y scene->m_p.y

static void	create_bmp_header(t_for_mlx *v, t_scene *scene, int fd)
{
	int				size_of_file;
	unsigned char	*header;

	size_of_file = HEADER_SIZE + INFO_SIZE + (v->bits_per_pixel / 8 * X * Y);
	header = my_calloc(HEADER_SIZE + INFO_SIZE, sizeof(unsigned char));
	header[0] = (unsigned char)('B');
	header[1] = (unsigned char)('M');
	header[2] = (unsigned char)(size_of_file);
	header[3] = (unsigned char)(size_of_file >> 8);
	header[4] = (unsigned char)(size_of_file >> 16);
	header[5] = (unsigned char)(size_of_file >> 24);
	header[10] = (unsigned char)(HEADER_SIZE + INFO_SIZE);
	header[HEADER_SIZE + 0] = (unsigned char)(INFO_SIZE);
	header[HEADER_SIZE + 4] = (unsigned char)(X);
	header[HEADER_SIZE + 5] = (unsigned char)(X >> 8);
	header[HEADER_SIZE + 6] = (unsigned char)(X >> 16);
	header[HEADER_SIZE + 7] = (unsigned char)(X >> 24);
	header[HEADER_SIZE + 8] = (unsigned char)(Y);
	header[HEADER_SIZE + 9] = (unsigned char)(Y >> 8);
	header[HEADER_SIZE + 10] = (unsigned char)(Y >> 16);
	header[HEADER_SIZE + 11] = (unsigned char)(Y >> 24);
	header[HEADER_SIZE + 12] = (unsigned char)(1);
	header[HEADER_SIZE + 14] = (unsigned char)(v->bits_per_pixel);
	write(fd, header, HEADER_SIZE + INFO_SIZE);
	free(header);
}

void		my_save_bmp(t_scene *scene, t_for_mlx *vars)
{
	int	fd;
	int	height;

	height = scene->m_p.y;
	if (!(fd = open("myrt.bmp", O_CREAT | O_WRONLY | O_TRUNC | O_APPEND, 0644)))
		my_error("It is impossible to create bmp file\n");
	create_bmp_header(vars, scene, fd);
	while (--height)
		vars->addr += scene->for_mlx->line_length;
	while (height < scene->m_p.y)
	{
		write(fd, vars->addr, scene->m_p.x * 4);
		vars->addr -= scene->for_mlx->line_length;
		height++;
	}
	close(fd);
}
