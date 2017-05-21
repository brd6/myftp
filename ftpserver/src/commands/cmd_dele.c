/*
** cmd_dele.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 12:34:19 2017 bongol_b
** Last update Sun May 21 21:25:13 2017 Berdrigue Bongolo-Beto
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"

int		cmd_dele_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  remove(args[1]);
  send_msg_response(sock_fd, "250", NULL);
  return (1);
}
