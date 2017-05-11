/*
** cmd_user.c for myftp in /home/bongol_b/Epitech-rendu/TEK2/B4 - Systeme Unix - Réseau/PSU_2016_myftp/ftpserver
**
** Made by bongol_b
** Login   <bongol_b@epitech.net>
**
** Started on  Thu May 11 18:47:14 2017 bongol_b
** Last update Thu May 11 22:26:21 2017 bongol_b
*/

#include <string.h>
#include "myftp_server.h"
#include "debug.h"

int		cmd_user_execute(int sock_fd, const char **args)
{
  PRINT_DEBUG("cmd_user_execute");
  if (args[0] == NULL || args[1] == NULL)
    return (0);
  strcpy(g_config.current_user.name, args[1]);
  PRINT_DEBUG("cmd_user_execute: user_name=%s", g_config.current_user.name);
  return (1);
}
