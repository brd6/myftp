/*
** socket_debug_utils.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 11:27:41 2017 bongol_b
** Last update Wed May 10 22:01:22 2017 bongol_b
*/

#include <arpa/inet.h>
#include <sys/types.h>
#include <sys/socket.h>
#include "debug.h"

void			debug_socket_address(int sock_fd)
{
  struct sockaddr_in	sock_address;
  socklen_t		len;

  len = sizeof(struct sockaddr_in);
  if (getsockname(sock_fd, (struct sockaddr *) &sock_address, &len) < 0)
    return ;
  PRINT_DEBUG("ip=%s, port=%u", inet_ntoa(sock_address.sin_addr),
	      ntohs(sock_address.sin_port));
}

void			debug_socket_distance_address(int sock_fd)
{
  struct sockaddr_in	sock_address;
  socklen_t		len;

  len = sizeof(struct sockaddr_in);
  if (getpeername(sock_fd, (struct sockaddr *) &sock_address, &len) < 0)
    return ;
  PRINT_DEBUG("ip=%s, port=%u", inet_ntoa(sock_address.sin_addr),
	      ntohs(sock_address.sin_port));
}
