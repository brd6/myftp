/*
** cmd_noop.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:18:30 2017 bongol_b
** Last update Sun May 21 21:25:54 2017 Berdrigue Bongolo-Beto
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"

int		cmd_noop_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  send_msg_response(sock_fd, "200", NULL);
  return (1);
}
