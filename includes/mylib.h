#ifndef MYLIB_H
# define MYLIB_H

# include <stdlib.h>
# include <unistd.h>
# ifndef BUFFER_SIZE
#  define BUFFER_SIZE 32
# endif

void	*my_memset(void *memptr, int val, size_t len);
void	my_bzero(void *str, size_t n);
int		my_strlen(const char *str);
int		my_strncmp(const char *str1, const char *str2, size_t n);
int		my_atoi(char *str);
double	my_atof(char *str);
int		my_isalpha(int smbl);
int		my_isdigit(int smbl);
char	*my_skip_space(char *line);
void	*my_calloc(size_t count, size_t size);
char	*my_substr(char const *str, unsigned int start, int len);
char	**my_split(char *str);
int		get_line_from_file(int fd, char **line);

#endif
