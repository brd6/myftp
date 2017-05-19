/*
** get_next_line.c for get_next_line in /home/bongol_b/rendu/get_next_line
**
** Made by berdrigue bongolo-beto
** Login   <bongol_b@epitech.net>
**
** Started on  Sun Dec 27 13:06:29 2015 berdrigue bongolo-beto
** Last update Fri May 19 17:36:45 2017 bongol_b
*/

#include "get_next_line.h"

void		save_buff(int line_pos, char buff[READ_SIZE])
{
  int		j;

  if (line_pos < 0 || buff[0] == 0)
    return ;
  j = 0;
  while (buff[line_pos++])
    {
      buff[j++] = buff[line_pos];
    }
  buff[j] = 0;
}

int		my_strxlen(char *str)
{
  int		i;

  i = 0;
  if (str == NULL)
    return (0);
  while (str[i])
    i++;
  return (i);
}

char		*my_realloc_str(char *str, int size_to_add)
{
  char		*new_str;
  int		i;
  int		old_size;

  old_size = my_strxlen(str);
  size_to_add = size_to_add + old_size;
  if ((new_str = malloc(sizeof(*new_str) * (size_to_add + 1))) == NULL)
    return (NULL);
  i = 0;
  while (i < old_size)
    {
      new_str[i] = str[i];
      i++;
    }
  new_str[i] = 0;
  free(str);
  return (new_str);
}

char		*copy_curr_buff(char buff[READ_SIZE],
				char *line,
				int *line_pos,
				int ret)
{
  int		i;
  int		j;

  if (buff[0] == 0)
    return (line);
  i = 0;
  j = my_strxlen(line);
  if ((line = my_realloc_str(line, ret)) == NULL)
    return (NULL);
  while (buff[i])
    {
      if (buff[i] == '\n')
	break ;
      line[j + i] = buff[i];
      i++;
    }
  line[j + i] = 0;
  if (buff[i] == '\n')
    *line_pos = i;
  return (line);
}

char		*get_next_line(const int fd)
{
  int		ret;
  static char	buff[READ_SIZE];
  char		*line;
  int		line_pos;

  line = NULL;
  ret = READ_SIZE;
  line_pos = -1;
  while (READ_SIZE > 0)
    {
      line = copy_curr_buff(buff, line, &line_pos, ret);
      save_buff(line_pos, buff);
      if (line_pos != -1 || ret == 0)
	return (line);
      if ((ret = read(fd, buff, READ_SIZE)) < 0)
	break ;
      buff[ret] = 0;
    }
  free(line);
  return (NULL);
}
