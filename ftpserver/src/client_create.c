/*
** client_create.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Sun May 14 11:30:25 2017 bongol_b
** Last update Sun May 14 11:44:51 2017 bongol_b
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "myftp_server.h"
#include "errors.h"
#include "debug.h"

static void	init_sock_address(struct sockaddr_in *sock_address,
				  const char *addr,
				  uint16_t port)
{
  memset(sock_address, 0, sizeof(*sock_address));
  sock_address->sin_family = AF_INET;
  sock_address->sin_port = htons(port);
  inet_aton(addr, &(sock_address->sin_addr));
}

int		client_create(const char *addr, uint16_t port)
{
  int		sock_fd;
  t_sockaddr_in	sockaddr_in;
  int		connected;

  if ((sock_fd = socket(AF_INET, SOCK_STREAM, 0)) == -1)
    return (0);
  init_sock_address(&sockaddr_in, addr, port);
  connected = connect(sock_fd, (t_sockaddr *)&sockaddr_in, sizeof(t_sockaddr));
  return (connected != -1 ? sock_fd : -1);
}
