/*
** myftp_server.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 08:25:08 2017 bongol_b
** Last update Thu May 11 01:05:01 2017 bongol_b
*/

#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <unistd.h>
#include <stdio.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "myftp_server.h"
#include "errors.h"
#include "debug.h"

static int		wait_client_sock_connection(t_config const *config,
						    int *client_sock_fd,
						    struct sockaddr_in *addr,
						    socklen_t *sock_len)
{
  *client_sock_fd = accept(config->sock_fd,
			  (struct sockaddr *)addr,
			  sock_len);
  if (*client_sock_fd == -1)
    return (dprintf(2, ERR_SOCKET_ACCEPT, strerror(errno)), 0);
  PRINT_DEBUG("client connected !");
  debug_socket_distance_address(*client_sock_fd);
  return (1);
}

static int		handler_new_client(t_config const *config,
					   int client_sock_fd)
{
  int			child_pid;

  PRINT_DEBUG("handle new client");
  if ((child_pid = fork()) == 0)
    {
      close(config->sock_fd);
      service_handler(config, client_sock_fd);
      close(client_sock_fd);
      PRINT_DEBUG("child process finished");
      exit(1);
    }
  close(client_sock_fd);
  return (1);
}

int			server_run(t_config const *config, t_user const *user)
{
  int			client_sock_fd;
  struct sockaddr_in	client_addr;
  socklen_t		sock_len;

  while (!g_stop)
    {
      PRINT_DEBUG("server waiting for a client connection...");
      if (wait_client_sock_connection(config,
				      &client_sock_fd,
				      &client_addr,
				      &sock_len) == 1)
	handler_new_client(config, client_sock_fd);
    }
  PRINT_DEBUG("server stop");
  (void)user;
  return (1);
}
