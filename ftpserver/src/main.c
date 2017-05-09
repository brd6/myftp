/*
** main.c for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:35:16 2017 Berdrigue Bongolo-Beto
** Last update Mon May  8 17:16:45 2017 Berdrigue Bongolo-Beto
*/

#include <stdio.h>
#include "myftp_server.h"

int		main(int ac, char **av)
{
  int		port;
  char		*path;

  if (ac != 3)
    {
      dprintf(2, USAGE, av[0]);
      return (1);
    }
  port = atoi(av[1]);
  path = av[2];
  return (0);
}
