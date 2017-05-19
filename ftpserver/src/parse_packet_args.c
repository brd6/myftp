/*
** parse_packet_args.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Sun May 14 22:34:57 2017 bongol_b
** Last update Fri May 19 13:40:28 2017 bongol_b
*/

#include <stdlib.h>
#include <stdio.h>
#include "myftp_server.h"
#include "errors.h"
#include "debug.h"

static void	init_vars(int *i, int *j, int *k)
{
  *i = 0;
  *j = 0;
  *k = 0;
}

static char	**parse_args(const char *str)
{
  char		**args;
  int		i;
  int		j;
  int		k;

  if (((args = malloc(sizeof(*args) * 3)) == NULL) ||
      (((args[0] = malloc(sizeof(**args) * BUFF_SIZE)) == NULL) ||
       ((args[1] = malloc(sizeof(**args) * BUFF_SIZE)) == NULL)))
    return (NULL);
  init_vars(&i, &j, &k);
  while (str && str[i])
    {
      if (j == 0 && (str[i] == ' ' || str[i] == '\t'))
	{
	  args[j][k] = 0;
	  j = 1;
	  k = 0;
	}
      else
	args[j][k++] = str[i];
      i++;
    }
  args[j][k] = 0;
  args[j + 1] = NULL;
  return (args);
}

char		**parse_packet_args(int sock_fd)
{
  char		buff[PACKET_BUFF_SIZE];
  char		**args;

  args = NULL;
  if (packet_receive(sock_fd, buff) == 0)
    return (NULL);
  if (strlen(buff) < 1)
    return (NULL);
  if (((args = parse_args(buff)) == NULL ||
       my_wordtab_count((const char **)args) < 1))
    return (my_free_wordtab(args), NULL);
  return (args);
}
