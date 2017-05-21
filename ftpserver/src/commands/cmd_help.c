/*
** cmd_help.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:16:41 2017 bongol_b
** Last update Sun May 21 21:25:46 2017 Berdrigue Bongolo-Beto
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"

int		cmd_help_execute(int sock_fd, const char **args)
{
  char		buff[BUFF_SIZE];

  if (args[0] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  strcpy(buff, "214 The following commands are recognized.\r\n");
  packet_send(sock_fd, buff);
  memset(buff, 0,  BUFF_SIZE);
  get_debug_available_cmds(buff);
  packet_send(sock_fd, buff);
  send_msg_response(sock_fd, "214", NULL);
  return (1);
}
