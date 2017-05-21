/*
** cmd_size.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Mon May 15 16:17:38 2017 bongol_b
** Last update Sun May 21 21:27:02 2017 Berdrigue Bongolo-Beto
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"

int		cmd_size_execute(int sock_fd, const char **args)
{
  char		buff[BUFF_SIZE];
  int		size;

  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if ((size = get_file_size(args[1])) == -1)
    send_msg_response(sock_fd, "550", NULL);
  sprintf(buff, "%d", get_file_size(args[1]));
  send_msg_response(sock_fd, "213", buff);
  return (1);
}
