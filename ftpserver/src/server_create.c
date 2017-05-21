/*
** server_create.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 11:04:14 2017 bongol_b
** Last update Sun May 21 21:18:52 2017 Berdrigue Bongolo-Beto
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
					  unsigned int addr,
					  unsigned short port)
{
  memset(sock_address, 0, sizeof(*sock_address));
  sock_address->sin_family = AF_INET;
  sock_address->sin_port = htons(port);
  sock_address->sin_addr.s_addr = htonl(addr);
}

static int		set_reuse_addr_mode(int sock_fd)
{
  int			optval;
  int			ret;

  optval = 1;
  ret = setsockopt(sock_fd, SOL_SOCKET, SO_REUSEADDR, &optval, sizeof(optval));
  return (ret != -1);
}

int		init_sock_addr(int sock_fd,
			       struct sockaddr_in *sock_addr)
{
  socklen_t	len;

  len = sizeof(struct sockaddr_in);
  if (getsockname(sock_fd, (struct sockaddr *) sock_addr, &len) < 0)
    return (0);
  return (1);
}

int			server_create(unsigned int addr,
				      unsigned short port,
				      int reuse_addr)
{
  int			sock_fd;
  struct sockaddr_in	sock_address;
  int			ret;

  sock_fd = -1;
  init_sock_address(&sock_address, addr, port);
  if ((sock_fd = socket(sock_address.sin_family, SOCK_STREAM, 0)) == -1)
    return (dprintf(2, ERR_INIT_SOCKET), -1);
  if (reuse_addr && !set_reuse_addr_mode(sock_fd))
    return (dprintf(2, ERR_SOCKET_OPT), -1);
  ret = bind(sock_fd, (struct sockaddr *)&sock_address, sizeof(sock_address));
  if (ret == -1)
    {
      close(sock_fd);
      return (dprintf(2, ERR_INIT_SOCKET_BIND), -1);
    }
  if (listen(sock_fd, SERVER_LISTEN_BACKLOG) == -1)
    {
      close(sock_fd);
      return (dprintf(2, ERR_INIT_SOCKET_LISTEN), -1);
    }
  return (sock_fd);
}
