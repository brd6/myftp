/*
** my_free_wordtab.c for my_free_wordtab in /home/bongol_b/Epitech-rendu/libmy
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Sun Feb 21 18:52:03 2016 Berdrigue BONGOLO BETO
** Last update Thu May 11 21:06:17 2017 bongol_b
*/

#include <stdlib.h>

void		my_free_wordtab(char **tab)
{
  int		i;

  i = 0;
  while (tab && tab[i])
    free(tab[i++]);
  free(tab);
  tab = NULL;
}
