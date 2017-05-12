/*
** cmd_user.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 18:47:14 2017 bongol_b
** Last update Fri May 12 11:14:23 2017 bongol_b
*/

#include <string.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_user_execute(int sock_fd, const char **args)
{
  if (args[0] == NULL || args[1] == NULL)
    return (send_msg_response(sock_fd, "530", NULL), 0);
  if (g_config.current_user.is_auth)
    return (send_msg_response(sock_fd, "530", NULL), 0);
  strcpy(g_config.current_user.name, args[1]);
  PRINT_DEBUG("cmd_user_execute: user_name=%s sock_fd=%d",
	      g_config.current_user.name,
	      sock_fd);
  send_msg_response(sock_fd, "331", NULL);
  return (1);
}
