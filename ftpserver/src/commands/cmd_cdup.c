/*
** cmd_cdup.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 12:30:28 2017 bongol_b
** Last update Fri May 12 12:31:55 2017 bongol_b
*/

#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_cdup_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  chdir("..");
  send_msg_response(sock_fd, "250", NULL);
  (void)args;
  return (1);
}
