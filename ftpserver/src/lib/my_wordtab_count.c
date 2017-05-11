/*
** my_wordtab_count.c for my_wordtab_count in /home/bongol_b/rendu/PSU_2015_minishell1/lib/my
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Fri Jan  8 02:36:27 2016 Berdrigue BONGOLO BETO
** Last update Fri Jun  3 20:28:30 2016 Berdrigue BONGOLO BETO
*/

int		my_wordtab_count(const char **tab)
{
  int		i;

  i = 0;
  while (tab[i])
    i++;
  return (i);
}
