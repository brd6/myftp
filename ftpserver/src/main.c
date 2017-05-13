/*
** main.c for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:35:16 2017 Berdrigue Bongolo-Beto
** Last update Sat May 13 13:02:39 2017 bongol_b
*/

#include <signal.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "debug.h"
#include "errors.h"
#include "myftp_server.h"

t_config	g_config;

static int	run(char *default_user_path, int port)
{
  PRINT_DEBUG("server pid=%d", getpid());
  if (signal(SIGCHLD, SIG_IGN) == SIG_ERR)
    return (dprintf(2, ERR_SET_SIGNAL), 0);
  g_config.port = port;
  g_config.sock_fd = -1;
  g_config.client_sock_fd = -1;
  g_config.parent_pid = getpid();
  if (server_create(&(g_config.sock_fd), g_config.port) == 0)
    return (dprintf(2, ERR_SERVER_CREATE, g_config.port), 0);
  if (user_change_home("anonymous", default_user_path) == 0)
    return (dprintf(2, ERR_USER_CHANGE_DIR), 0);
  server_run();
  close(g_config.sock_fd);
  return (1);
}

void		sigint_handler(int sig)
{
  g_config.should_stop = 1;
  (void)sig;
  if (g_config.parent_pid == getpid())
    {
      if (g_config.sock_fd > -1)
	close(g_config.sock_fd);
      PRINT_WARNING("stop server");
    }
  else
    {
      if (g_config.client_sock_fd > -1)
	close(g_config.client_sock_fd);
      PRINT_WARNING("stop client communication");
    }
  exit(0);
}

int		main(int ac, char **av)
{
  int		port;

  g_config.should_stop = 0;
  signal(SIGINT, sigint_handler);
  signal(SIGCHLD, SIG_IGN);
  signal(SIGTERM, sigint_handler);
  if (ac != 3)
    {
      dprintf(2, USAGE, av[0]);
      return (1);
    }
  if ((port = atoi(av[1])) < 1)
    return (dprintf(2, ERR_PROG_FIRST_ARG), 1);
  return (!run(av[2], atoi(av[1])));
}
