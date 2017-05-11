/*
** my_str_split.c for my_str_plit in /home/bongol_b/rendu/Piscine_C_bistromathique
**
** Made by berdrigue bongolo-beto
** Login   <bongol_b@epitech.net>
**
** Started on  Wed Oct 28 21:43:17 2015 berdrigue bongolo-beto
** Last update Thu May 11 21:27:27 2017 bongol_b
*/

#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "myftp_server.h"

int	count_word(const char *str, const char *sp)
{
  int	i;
  int	nb_word;

  i = 0;
  nb_word = 0;
  while (str && str[i])
    {
      if (my_get_char_pos(sp, str[i]) == -1)
        {
          nb_word = nb_word + 1;
          while ((my_get_char_pos(sp, str[i]) == -1) && str[i])
	    i = i + 1;
          i = i - 1;
        }
      i = i + 1;
    }
  return (nb_word);
}

void	my_str_split_init(int *k, int *j, int *i)
{
  *k = 0;
  *j = 0;
  *i = 0;
}

void	my_str_split_end(char **tab, int *k, int *j)
{
  tab[*j][*k] = '\0';
  *k = 0;
  *j = *j + 1;
}

void	my_str_split_end2(int j, char **tab)
{
  if (j > 1 && tab[j - 1][0] == 0)
    tab[j - 1] = 0;
  tab[j] = 0;
}

char	**my_str_split(const char *str, const char *sp)
{
  char	**tab;
  int	i;
  int	j;
  int	k;

  my_str_split_init(&k, &j, &i);
  if ((tab = malloc(sizeof(char *) * (count_word(str, sp) + 2))) == NULL)
    return (NULL);
  while (str[i])
    {
      if ((tab[j] = malloc(sizeof(char) * strlen(str) + 2)) == NULL)
	return (NULL);
      while ((my_get_char_pos(sp, str[i]) != -1) && str[i])
	i = i + 1;
      while ((my_get_char_pos(sp, str[i]) == -1) && str[i])
	{
	  tab[j][k] = str[i];
	  i = i + 1;
	  k = k + 1;
	}
      my_str_split_end(tab, &k, &j);
    }
  my_str_split_end2(j, tab);
  return (tab);
}
