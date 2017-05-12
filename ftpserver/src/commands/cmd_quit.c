/*
** cmd_quit_execute.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 09:45:52 2017 bongol_b
** Last update Fri May 12 09:50:57 2017 bongol_b
*/

#include <stdio.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_quit_execute(int sock_fd, const char **args)
{
  int		is_auth;

  PRINT_DEBUG("cmd_quit_execute");
  g_config.should_stop = 1;
  send_msg_response(sock_fd, "221", NULL);
  (void)args;
  return (1);
}
