/*
** cmd_type.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Sun May 14 21:26:39 2017 bongol_b
** Last update Sun May 14 21:36:58 2017 bongol_b
*/

#include <string.h>
#include <stdlib.h>
#include "myftp_server.h"

int		cmd_type_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if (strcmp(args[1], "A") == 0)
    g_config.data_type = ASCII;
  else if (strcmp(args[1], "I") == 0)
    g_config.data_type = BINARY;
  else
    return (send_msg_response(sock_fd, "500", NULL), 0);
  send_msg_response(sock_fd, "200", NULL);
  return (1);
}
