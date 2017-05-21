/*
** cmd_pwd.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Fri May 12 11:46:46 2017 bongol_b
** Last update Sun May 21 21:25:06 2017 Berdrigue Bongolo-Beto
*/

#include <unistd.h>
#include <string.h>
#include <stdio.h>
#include "myftp_server.h"

static int	set_current_path()
{
  return (getcwd(g_config.current_path,sizeof(g_config.current_path)) != NULL);
}

int		cmd_pwd_execute(int sock_fd, const char **args)
{
  char		buff[PATH_MAX];

  if (!set_current_path())
    return (0);
  sprintf(buff, "'%s'", g_config.current_path);
  send_msg_response(sock_fd, "257", buff);
  (void)args;
  return (1);
}
