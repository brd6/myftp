/*
** packet_manager.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 14:55:49 2017 bongol_b
** Last update Sun May 21 21:22:18 2017 Berdrigue Bongolo-Beto
*/

#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "errors.h"
#include "get_next_line.h"

int		packet_send(int socket_fd, char *buff)
{
  int		i;
  int		size;

  size = strlen(buff);
  if ((i = write(socket_fd, buff, size)) == -1)
    return (dprintf(2, ERR_WRITE), 0);
  return (1);
}

int		packet_send_raw(int socket_fd, char *buff, int size)
{
  int		i;

  if ((i = write(socket_fd, buff, size)) == -1)
    return (dprintf(2, ERR_WRITE), 0);
  return (1);
}

int		packet_receive(int socket_fd, char *buff)
{
  int		i;

  if ((i = read(socket_fd, buff, PACKET_BUFF_SIZE)) == -1)
    return (dprintf(2, ERR_READ), 0);
  buff[i] = 0;
  if (strncmp(&buff[strlen(buff) - 2], "\r\n", 2) == 0)
    {
      buff[strlen(buff) - 1] = '\n';
      buff[strlen(buff) - 2] = 0;
    }
  if (i > 0 && buff[i - 1] == '\n')
    buff[i - 1] = 0;
  else
    g_config.should_stop = 1;
  buff[i] = 0;
  return (1);
}

char		*packet_receive_gnl(int socket_fd)
{
  char		*buff;
  int		i;

  if ((buff = get_next_line(socket_fd)) == NULL)
    {
      g_config.should_stop = 1;
      return (NULL);
    }
  i = strlen(buff);
  if (i == 0)
    return (NULL);
  if (i > 1 && strncmp(&buff[i - 1], "\r", 1) == 0)
    buff[i - 1] = 0;
  return (buff);
}
