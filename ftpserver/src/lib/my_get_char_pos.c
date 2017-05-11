/*
** my_get_char_pos.c for my_get_char_pos in /home/bongol_b/rendu/Piscine_C_bistromathique
**
** Made by berdrigue bongolo-beto
** Login   <bongol_b@epitech.net>
**
** Started on  Fri Oct 30 17:49:30 2015 berdrigue bongolo-beto
** Last update Fri Jun  3 20:59:43 2016 Berdrigue BONGOLO BETO
*/

int	my_get_char_pos(const char *str, char c)
{
  int	i;

  i = 0;
  while (str && str[i])
    {
      if (str[i] == c)
	return (i);
      i = i + 1;
    }
  return (-1);
}
