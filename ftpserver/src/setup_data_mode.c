/*
** setup_data_mode.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Sun May 14 21:44:26 2017 bongol_b
** Last update Sun May 14 21:44:57 2017 bongol_b
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

int		setup_passive_mode(int sock_fd)
{
  socklen_t	addr_in_len;

  addr_in_len = sizeof(g_config.client.addr_in);
  send_msg_response(sock_fd, "150", NULL);
  PRINT_DEBUG("passive mode wait connection...");
  g_config.client.sock_data = accept(g_config.server.sock_data,
				     (t_sockaddr *)&g_config.client.addr_in,
				     &addr_in_len);
  if (g_config.client.sock_data == -1)
    {
      PRINT_ERROR("[passive] client data sock failed");
      return (0);
    }
  PRINT_DEBUG("[passive] client data sock success !");
  return (1);
}

int		setup_active_mode(int sock_fd)
{
  send_msg_response(sock_fd, "150", NULL);
  PRINT_DEBUG("Connection to %s at %d in progress..",
	      g_config.client.ipaddr,
	      g_config.client.port_data);
  g_config.client.sock_data = client_create(g_config.client.ipaddr,
					    g_config.client.port_data);
  if (g_config.client.sock_data == -1)
    {
      PRINT_ERROR("[active] client data sock failed");
      return (0);
    }
  PRINT_DEBUG("[active] client data sock success !");
  return (1);
}

void		close_data_mode()
{
  close(g_config.client.sock_data);
  g_config.client.sock_data = -1;
  if (g_config.data_mode == PASSIVE)
    {
      close(g_config.server.sock_data);
      g_config.server.sock_data = -1;
    }
}
