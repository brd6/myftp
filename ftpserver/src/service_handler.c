/*
** service_handle.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 23:42:04 2017 bongol_b
** Last update Thu May 11 17:51:57 2017 bongol_b
*/

#include <stdio.h>
#include "myftp_server.h"
#include "errors.h"
#include "debug.h"

static int	service_loop()
{
  return (1);
}

static int	service_stop()
{
  return (1);
}

static int	service_authentification(int sock_fd)
{
  char		buff[PACKET_BUFF_SIZE];
  int		ret;

  PRINT_DEBUG("service auth");
  ret = packet_receive(sock_fd, buff);
  PRINT_DEBUG("service auth : ret=%d", ret);
  return (1);
}

int		service_handler(t_config const *config, int client_sock_fd)
{
  if (send_msg_response(client_sock_fd, "220", NULL) == 0)
    return (dprintf(2, ERR_SEND_MSG), 0);
  service_authentification(client_sock_fd);
  (void)config;
  return (1);
}
