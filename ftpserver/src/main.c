/*
** main.c for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:35:16 2017 Berdrigue Bongolo-Beto
** Last update Thu May 11 15:03:52 2017 bongol_b
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "debug.h"
#include "errors.h"
#include "myftp_server.h"

int	g_stop;

static int	run(char *default_user_path, int port)
{
  t_config	config;
  t_user	anonymous_user;

  PRINT_DEBUG("server pid=%d", getpid());
  if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
    return (dprintf(2, ERR_SET_SIGNAL), 0);
  config.port = port;
  if (server_create(&(config.sock_fd), config.port) == 0)
    return (dprintf(2, ERR_SERVER_CREATE, config.port), 0);
  if (user_create(&anonymous_user, "Anonymous", NULL, default_user_path) == 0)
    return (dprintf(2, ERR_CREATE_USER), 0);
  server_run(&config, &anonymous_user);
  close(config.sock_fd);
  return (1);
}

void		sigint_handler(int sig)
{
  g_stop = 1;

  (void)sig;
}

int		main(int ac, char **av)
{
  int		port;

  g_stop = 0;
  /* signal(SIGINT, sigint_handler); */
  if (ac != 3)
    {
      dprintf(2, USAGE, av[0]);
      return (1);
    }
  if ((port = atoi(av[1])) < 1)
    return (dprintf(2, ERR_PROG_FIRST_ARG), 1);
  return (!run(av[2], atoi(av[1])));
}
