/*
** main.c for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:35:16 2017 Berdrigue Bongolo-Beto
** Last update Wed May 10 10:18:37 2017 bongol_b
*/

#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "errors.h"
#include "myftp_server.h"

static int	run(char *default_user_path, int port)
{
  int		server_sock_fd;

  if (server_create(&server_sock_fd, port) == 0)
    return (dprintf(2, ERR_SERVER_CREATE, port), 0);
  close(server_sock_fd);
  (void)default_user_path;
  return (1);
}

int		main(int ac, char **av)
{
  int		port;

  if (ac != 3)
    {
      dprintf(2, USAGE, av[0]);
      return (1);
    }
  if ((port = atoi(av[1])) < 0)
    return (dprintf(2, ERR_PROG_FIRST_ARG), 1);
  return (!run(av[2], atoi(av[1])));
}
