/*
** cmd_pass.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 19:15:02 2017 bongol_b
** Last update Fri May 12 09:23:52 2017 bongol_b
*/

#include <stdio.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_pass_execute(int sock_fd, const char **args)
{
  int		is_auth;

  PRINT_DEBUG("cmd_pass_execute");
  if (args[0] == NULL ||
      g_config.current_user.name[0] == 0)
    return (0);
  if (args[1] != NULL)
    strcpy(g_config.current_user.pass, args[1]);
  else
    g_config.current_user.pass[0] = 0;
  PRINT_DEBUG("cmd_pass_execute: pass=%s", g_config.current_user.pass);
  is_auth = user_try_auth(g_config.current_user.name,
			  g_config.current_user.pass);
  if (!is_auth)
    {
      PRINT_DEBUG("cmd_pass_execute: fail.");
      return (send_msg_response(sock_fd, "530", NULL), 0);
    }
  PRINT_DEBUG("cmd_pass_execute: success !");
  return (send_msg_response(sock_fd, "230", NULL), 1);
}
