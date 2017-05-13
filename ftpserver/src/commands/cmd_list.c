/*
** cmd_list.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver/src
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 22:23:26 2017 bongol_b
** Last update Sat May 13 11:11:44 2017 bongol_b
*/

#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_list_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  // TODO
  send_msg_response(sock_fd, "250", NULL);
  return (1);
}
