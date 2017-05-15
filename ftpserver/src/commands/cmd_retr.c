/*
** cmd_retr.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:21:38 2017 bongol_b
** Last update Mon May 15 10:33:29 2017 bongol_b
*/

#include <stdlib.h>
#include <fcntl.h>
#include <sys/stat.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

static int	send_file_ascii(int sock_fd, const char *file_name)
{
  int		fd;
  int		res;
  char		buff[PACKET_BUFF_SIZE + 1];
  char		*clean_content;

  if ((fd = open(file_name, O_RDONLY)) == -1)
    return (0);
  while ((res = read(fd, buff, PACKET_BUFF_SIZE)) > 0)
    {
      buff[res] = 0;
      clean_content = my_str_replace("\n", "\r\n", buff, -1);
      if (packet_send_raw(sock_fd, clean_content, res) == 0)
	{
	  PRINT_ERROR("can't send raw data. Connection out");
	  free(clean_content);
	  close(fd);
	  return (0);
	}
      free(clean_content);
    }
  close(fd);
  return (1);
}

static int	send_file_binary(int sock_fd, const char *file_name)
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
	  close(fd);
	  return (0);
	}
    }
  close(fd);
  return (1);
}

static int	send_file(int sock_fd, const char *file_name)
{
  if (g_config.data_type == ASCII)
    return (send_file_ascii(sock_fd, file_name));
  return (send_file_binary(sock_fd, file_name));
}

int		cmd_retr_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if (setup_data_mode(sock_fd) == 0)
    return (0);
  if (!send_file(g_config.client.sock_data, args[1]))
    return (send_msg_response(sock_fd, "500", NULL), 0);
  send_msg_response(sock_fd, "226", NULL);
  close_data_mode();
  return (1);
}
