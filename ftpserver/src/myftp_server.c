/*
** myftp_server.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 08:25:08 2017 bongol_b
** Last update Wed May 10 10:15:07 2017 bongol_b
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "myftp_server.h"
#include "errors.h"

static void		init_sock_address(struct sockaddr_in *sock_address,
					  int port)
{
  memset(sock_address, 0, sizeof(*sock_address));
  sock_address->sin_family = AF_INET;
  sock_address->sin_port = htons(port);
  sock_address->sin_addr.s_addr = htonl(INADDR_ANY);
}

static int		init_socket(int *sock_fd,
				    struct sockaddr_in *sock_address)
{
  int			ret;

  if ((*sock_fd = socket(sock_address->sin_family, SOCK_STREAM, 0)) == -1)
    return (dprintf(2, ERR_INIT_SOCKET), 0);
  ret = bind(*sock_fd, (struct sockaddr *)sock_address, sizeof(*sock_address));
  if (ret == -1)
    {
      close(*sock_fd);
      return (dprintf(2, ERR_INIT_SOCKET_BIND), 0);
    }
  if (listen(*sock_fd, SERVER_LISTEN_BACKLOG) == -1)
    {
      close(*sock_fd);
      return (dprintf(2, ERR_INIT_SOCKET_LISTEN), 0);
    }
  return (1);
}

int			server_create(int *sock_fd, int port)
{
  struct sockaddr_in	sock_address;

  init_sock_address(&sock_address, port);
  return (init_socket(sock_fd, &sock_address));
}
