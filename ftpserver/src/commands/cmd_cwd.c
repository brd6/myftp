/*
** cmd_cwd.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 12:12:04 2017 bongol_b
** Last update Sun May 14 22:22:52 2017 bongol_b
*/

#include <unistd.h>
#include <string.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_cwd_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "550", NULL), 0);
  if (chdir(args[1]) == -1)
    return (send_msg_response(sock_fd, "550", NULL));
  send_msg_response(sock_fd, "250", NULL);
  return (1);
}
