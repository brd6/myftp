/*
** cmd_retr.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:21:38 2017 bongol_b
** Last update Sun May 14 21:17:36 2017 bongol_b
*/

#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

static int	setup_passive_mode(int sock_fd)
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

static int	setup_active_mode(int sock_fd)
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

static void	close_data_mode()
{
  close(g_config.client.sock_data);
  g_config.client.sock_data = -1;
  if (g_config.data_mode == PASSIVE)
    {
      close(g_config.server.sock_data);
      g_config.server.sock_data = -1;
    }
}

static int	send_file(int sock_fd, const char *file_name)
{
  int		fd;
  int		res;
  char		buff[PACKET_BUFF_SIZE + 1];

  if ((fd = open(file_name, O_RDONLY)) == -1)
    return (0);
  while ((res = read(fd, buff, PACKET_BUFF_SIZE)) > 0)
    {
      if (packet_send_raw(sock_fd, buff, res) == 0)
	{
	  PRINT_ERROR("can't send raw data. Connection out");
	  return (0);
	}
    }
  return (1);
}

int		cmd_retr_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if (g_config.data_mode == _NONE)
    return (send_msg_response(sock_fd, "425", NULL), 0);
  if (g_config.data_mode == PASSIVE && !setup_passive_mode(sock_fd))
    return (send_msg_response(sock_fd, "425", NULL), 0);
  else if (!setup_active_mode(sock_fd))
    return (send_msg_response(sock_fd, "425", NULL), 0);
  //char *bff = execute_system_command("cat 5ko.dat");
  //PRINT_ERROR("bff='%s'", bff);
  send_file(g_config.client.sock_data, args[1]);
  send_msg_response(sock_fd, "226", NULL);
  close_data_mode();
  return (1);
}
