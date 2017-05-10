/*
** main.c for myftp in /home/bongol_b/Epitech-rendu/tek2/PSU_2016_myftp/server
**
** Made by Berdrigue Bongolo-Beto
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May  8 16:35:16 2017 Berdrigue Bongolo-Beto
** Last update Wed May 10 11:07:48 2017 bongol_b
*/

#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>
#include "errors.h"
#include "myftp_server.h"

static int	create_user(t_user *user,
			    char const *name,
			    char const *passwd,
			    char const *path)
{
  if ((user->name = strdup(name)) == NULL)
    return (0);
  if (passwd)
    {
      if ((user->password = strdup(passwd)) == NULL)
	return (0);
    }
  else
    user->password = NULL;
  if ((user->home_dir = strdup(path)) == NULL)
    return (0);
  return (1);
}

static int	run(char *default_user_path, int port)
{
  t_config	config;
  t_user	anonymous_user;

  config.port = port;
  if (server_create(&(config.sock_fd), config.port) == 0)
    return (dprintf(2, ERR_SERVER_CREATE, config.port), 0);
  if (create_user(&anonymous_user, "anonymous", NULL, default_user_path) == 0)
    return (dprintf(2, ERR_CREATE_USER), 0);
  server_run(&config, &anonymous_user);
  close(config.sock_fd);
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
  if ((port = atoi(av[1])) < 1)
    return (dprintf(2, ERR_PROG_FIRST_ARG), 1);
  return (!run(av[2], atoi(av[1])));
}
