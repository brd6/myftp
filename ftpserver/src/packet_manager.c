/*
** packet_manager.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 14:55:49 2017 bongol_b
** Last update Sun May 14 20:53:05 2017 bongol_b
*/

#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"
#include "errors.h"

int		packet_send(int socket_fd, char *buff)
{
  int		i;
  int		size;

  PRINT_DEBUG("packet_send - buff='%s'", buff);
  size = strlen(buff);
  if ((i = write(socket_fd, buff, size)) == -1)
    return (dprintf(2, ERR_WRITE), 0);
  PRINT_DEBUG("packet_send - send=%d rmnd=%d", i, size - i);
  return (1);
}

int		packet_send_raw(int socket_fd, char *buff, int size)
{
  int		i;

  if ((i = write(socket_fd, buff, size)) == -1)
    return (dprintf(2, ERR_WRITE), 0);
  PRINT_DEBUG("packet_send - send=%d rmnd=%d", i, size - i);
  return (1);
}

int		packet_receive(int socket_fd, char *buff)
{
  int		i;

  PRINT_DEBUG("packet_receive");
  if ((i = read(socket_fd, buff, PACKET_BUFF_SIZE)) == -1)
    return (dprintf(2, ERR_READ), 0);
  PRINT_DEBUG("packet_receive - recv=%d rmnd=%d", i, PACKET_BUFF_SIZE - i);
  buff[i] = 0;
  if (strncmp(&buff[strlen(buff) - 2], "\r\n", 2) == 0)
    {
      buff[strlen(buff) - 1] = '\n';
      buff[strlen(buff) - 2] = 0;
    }
  if (i > 0 && buff[i - 1] == '\n')
    buff[i - 1] = 0;
  else
    {
      PRINT_WARNING("hard stop");
      g_config.should_stop = 1;
    }
  buff[i] = 0;
  PRINT_DEBUG("packet_receive - buff='%s'", buff);
  return (1);
}
