/*
** cmd_pass.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 19:15:02 2017 bongol_b
** Last update Sun May 21 21:24:34 2017 Berdrigue Bongolo-Beto
*/

#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include "myftp_server.h"

static void	update_connected_user_info()
{
  user_get(g_config.current_user.name, &g_config.current_user);
  g_config.current_user.is_auth = 1;
  chdir(g_config.current_user.home_dir);
}

int		cmd_pass_execute(int sock_fd, const char **args)
{
  int		is_auth;

  if (args[0] == NULL ||
      g_config.current_user.name[0] == 0)
    return (0);
  if (g_config.current_user.is_auth)
    return (send_msg_response(sock_fd, "230", NULL), 0);
  if (args[1] != NULL)
    strcpy(g_config.current_user.pass, args[1]);
  else
    g_config.current_user.pass[0] = 0;
  is_auth = user_try_auth(g_config.current_user.name,
			  g_config.current_user.pass);
  g_config.current_user.is_auth = is_auth;
  if (!is_auth)
    return (send_msg_response(sock_fd, "530", NULL), 0);
  update_connected_user_info();
  return (send_msg_response(sock_fd, "230", NULL), 1);
}
