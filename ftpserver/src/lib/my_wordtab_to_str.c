/*
** my_wordtab_to_str.c for my_wordtab_to_str in /home/bongol_b/rendu_ok/PSU_2015_minishell1
**
** Made by Berdrigue BONGOLO BETO
** Login   <bongol_b@epitech.net>
**
** Started on  Tue Jan 19 20:06:54 2016 Berdrigue BONGOLO BETO
** Last update Sun May 14 22:29:28 2017 bongol_b
*/

#include <string.h>
#include <stdlib.h>
#include "myftp_server.h"

static int	wordtab_word_count(const char **args)
{
  int		i;
  int		j;

  i = 0;
  j = 0;
  while (args && args[i])
    j += strlen(args[i++]);
  return (j);
}

char		*my_wordtab_to_str(const char **args, char sp)
{
  char		*arg;
  int		i;
  int		j;
  int		k;

  j = wordtab_word_count(args);
  i = 0;
  if ((arg = malloc(sizeof(*arg) * (j + my_wordtab_count(args) + 1))) == NULL)
    return (0);
  j = 0;
  k = 0;
  while (args && args[i])
    {
      if (args[i][k] != 0)
	arg[j++] = args[i][k++];
      else
	{
	  if (args[i + 1] != NULL)
	    arg[j++] = sp;
	  k = 0;
	  i++;
	}
    }
  arg[j] = 0;
  return (arg);
}
