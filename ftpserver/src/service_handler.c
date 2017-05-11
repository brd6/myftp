/*
** service_handle.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Wed May 10 23:42:04 2017 bongol_b
** Last update Thu May 11 15:25:32 2017 bongol_b
*/

#include <stdlib.h>
#include "myftp_server.h"

static int	service_loop()
{
  return (1);
}

static int	service_stop()
{
  return (1);
}

static int	service_authentification(int client_sock_fd)
{
  return (1);
}

void		service_handler(t_config const *config, int client_sock_fd)
{
  send_msg_response(client_sock_fd, "220", NULL);
  service_authentification(client_sock_fd);
  (void)config;
}
