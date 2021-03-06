/*
** setup_data_mode.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Sun May 14 21:44:26 2017 bongol_b
** Last update Sun May 21 21:29:32 2017 Berdrigue Bongolo-Beto
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"

int		setup_passive_mode()
{
  socklen_t	addr_in_len;

  addr_in_len = sizeof(g_config.client.addr_in);
  g_config.client.sock_data = accept(g_config.server.sock_data,
				     (t_sockaddr *)&g_config.client.addr_in,
				     &addr_in_len);
  return (g_config.client.sock_data != -1);
}

int		setup_active_mode()
{
  g_config.client.sock_data = client_create(g_config.client.ipaddr,
					    g_config.client.port_data);
  return (g_config.client.sock_data != -1);
}

void		close_data_mode()
{
  if (g_config.client.sock_data != -1)
    close(g_config.client.sock_data);
  g_config.client.sock_data = -1;
  if (g_config.data_mode == PASSIVE && g_config.server.sock_data != -1)
    {
      close(g_config.server.sock_data);
      g_config.server.sock_data = -1;
    }
}

int		setup_data_mode(int sock_fd)
{
  if (g_config.data_mode == _NONE)
    return (send_msg_response(sock_fd, "425", NULL), 0);
  if (g_config.data_mode == PASSIVE && !setup_passive_mode())
    return (send_msg_response(sock_fd, "425", NULL), 0);
  else if (g_config.data_mode == ACTIVE && !setup_active_mode())
    return (send_msg_response(sock_fd, "425", NULL), 0);
  return (1);
}
